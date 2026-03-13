import os
import random
import sys
import time
from pathlib import Path

from google import genai

# -----------------------------------------------------------------------------
# Config
# -----------------------------------------------------------------------------
MODEL_NAME = "models/gemini-2.5-pro"

MAX_BOOTSTRAP_FILES = 15

MAX_RETRIES = 6
BACKOFF_BASE_SECONDS = 2.0
BACKOFF_JITTER_SECONDS = 0.5

STATE_FILE = Path(".github/.ai_review_bootstrap_done")

REPO_ROOT = Path(__file__).resolve().parents[2]
PROMPTS_DIR = REPO_ROOT / ".github" / "prompts"

PROMPT_COMMON_PATH = PROMPTS_DIR / "common.md"
PROMPT_CPP_PATH = PROMPTS_DIR / "lang" / "cpp.md"
PROMPT_PY_PATH = PROMPTS_DIR / "lang" / "python.md"

client = genai.Client(api_key=os.environ["GEMINI_API_KEY"])


# -----------------------------------------------------------------------------
# Debug: list models
# -----------------------------------------------------------------------------
def list_models() -> None:
    print("[ai-review] listing models...")
    for m in client.models.list():
        name = getattr(m, "name", None)
        print(f"- {name}")


# -----------------------------------------------------------------------------
# Prompt loading
# -----------------------------------------------------------------------------
def load_text(path: Path) -> str:
    if not path.exists():
        raise FileNotFoundError(
            f"Prompt file not found: {path}\n"
            f"Expected prompts:\n"
            f"- {PROMPT_COMMON_PATH}\n"
            f"- {PROMPT_CPP_PATH}\n"
            f"- {PROMPT_PY_PATH}\n"
        )
    return path.read_text(encoding="utf-8")


PROMPT_COMMON = load_text(PROMPT_COMMON_PATH)
PROMPT_CPP = load_text(PROMPT_CPP_PATH)
PROMPT_PY = load_text(PROMPT_PY_PATH)


def build_prompt_for(file_path: str) -> str:
    ext = Path(file_path).suffix.lower()
    if ext in [".cpp", ".cc", ".cxx"]:
        return PROMPT_COMMON + "\n\n" + PROMPT_CPP
    if ext == ".py":
        return PROMPT_COMMON + "\n\n" + PROMPT_PY
    return PROMPT_COMMON


# -----------------------------------------------------------------------------
# IO helpers
# -----------------------------------------------------------------------------
def read_readme(folder: str) -> str:
    path = os.path.join(folder, "README.md")
    if not os.path.exists(path):
        return ""
    with open(path, encoding="utf-8") as f:
        return f.read()


# -----------------------------------------------------------------------------
# Gemini call with retry/backoff
# -----------------------------------------------------------------------------
def generate_with_retry(model: str, contents: str) -> str:
    last_err: Exception | None = None

    for attempt in range(1, MAX_RETRIES + 1):
        try:
            resp = client.models.generate_content(model=model, contents=contents)
            return resp.text or ""
        except Exception as e:
            last_err = e
            if attempt < MAX_RETRIES:
                sleep_s = (BACKOFF_BASE_SECONDS * (2 ** (attempt - 1))) + random.uniform(
                    0, BACKOFF_JITTER_SECONDS
                )
                print(f"[ai-review] request failed (attempt {attempt}/{MAX_RETRIES}): {e}")
                print(f"[ai-review] sleeping {sleep_s:.2f}s then retry...")
                time.sleep(sleep_s)

    raise last_err if last_err else RuntimeError("generate_with_retry failed")


def review(code: str, readme: str, file_path: str) -> str:
    prompt = build_prompt_for(file_path)
    full_prompt = (
        prompt + "\n\n[문제 설명]\n" + readme + "\n\n[풀이 코드]\n" + code
    )
    return generate_with_retry(MODEL_NAME, full_prompt)


# -----------------------------------------------------------------------------
# Target selection
# -----------------------------------------------------------------------------
def find_unreviewed_files() -> list[str]:
    targets: list[str] = []
    for root, _, files in os.walk("."):
        for f in files:
            if not f.endswith((".cpp", ".cc", ".cxx", ".py")):
                continue
            src = os.path.join(root, f)
            review_path = os.path.join(root, "REVIEW.md")
            if not os.path.exists(review_path):
                targets.append(src)
    return sorted(targets)


def parse_args(argv: list[str]) -> tuple[bool, bool, list[str]]:
    """
    Returns:
      bootstrap: whether to run bootstrap
      list_only: whether to print model list and exit
      files: push-changed files (space separated)
    """
    bootstrap = False
    list_only = False
    files: list[str] = []

    for a in argv[1:]:
        if a == "--bootstrap":
            bootstrap = True
        elif a == "--list-models":
            list_only = True
        else:
            files.extend(a.split())

    files = sorted(set(files))
    return bootstrap, list_only, files


# -----------------------------------------------------------------------------
# Main
# -----------------------------------------------------------------------------
def main() -> None:
    bootstrap, list_only, push_files = parse_args(sys.argv)

    print(f"[ai-review] model: {MODEL_NAME}")

    if list_only:
        list_models()
        return

    if bootstrap:
        if STATE_FILE.exists():
            print("[ai-review] Bootstrap already done; skipping.")
            return
        targets_all = find_unreviewed_files()
        targets = targets_all[:MAX_BOOTSTRAP_FILES]
        remaining = len(targets_all) - len(targets)
    else:
        targets = push_files
        remaining = 0

    if not targets:
        print("[ai-review] No targets.")
        return

    print(f"[ai-review] targets: {len(targets)} file(s)")
    if bootstrap:
        print(f"[ai-review] bootstrap remaining after this batch: {remaining}")

    for f in targets:
        with open(f, encoding="utf-8") as fp:
            code = fp.read()

        folder = os.path.dirname(f)
        readme = read_readme(folder)
        result = review(code, readme, f)

        out = os.path.join(folder, "REVIEW.md")
        with open(out, "w", encoding="utf-8") as w:
            w.write("# AI 코드 리뷰\n\n")
            w.write(f"- Model: `{MODEL_NAME}`\n")
            w.write(f"- Source: `{f}`\n\n")
            w.write(result)

    if bootstrap:
        if remaining <= 0:
            STATE_FILE.parent.mkdir(parents=True, exist_ok=True)
            STATE_FILE.write_text("done\n", encoding="utf-8")
            print(f"[ai-review] Wrote state file: {STATE_FILE}")
        else:
            print("[ai-review] Bootstrap not finished yet; state file not written.")

    print("[ai-review] Done.")


if __name__ == "__main__":
    main()