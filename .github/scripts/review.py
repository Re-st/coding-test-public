import os
import sys
from pathlib import Path

from google import genai

# -----------------------------------------------------------------------------
# Config
# -----------------------------------------------------------------------------
MODEL_NAME = "gemini-3-pro"
STATE_FILE = Path(".github/.ai_review_bootstrap_done")

REPO_ROOT = Path(__file__).resolve().parents[2]  # repo root
PROMPTS_DIR = REPO_ROOT / ".github" / "prompts"

PROMPT_COMMON_PATH = PROMPTS_DIR / "common.md"
PROMPT_CPP_PATH = PROMPTS_DIR / "lang" / "cpp.md"
PROMPT_PY_PATH = PROMPTS_DIR / "lang" / "python.md"

client = genai.Client(api_key=os.environ["GEMINI_API_KEY"])


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
# Gemini review
# -----------------------------------------------------------------------------
def review(code: str, readme: str, file_path: str) -> str:
    prompt = build_prompt_for(file_path)

    full_prompt = (
        prompt
        + "\n\n[문제 설명]\n"
        + readme
        + "\n\n[풀이 코드]\n"
        + code
    )

    resp = client.models.generate_content(
        model=MODEL_NAME,
        contents=full_prompt,
    )
    return resp.text or ""


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

    return targets


def list_models() -> None:
    print("[ai-review] listing models...")
    for m in client.models.list():
        name = getattr(m, "name", None)
        # name이 보통 'models/xxx' 형태로 옴
        print(f"- {name}")

def parse_args(argv: list[str]) -> tuple[bool, bool, list[str]]:
    """
    Usage:
      python .github/scripts/review.py --bootstrap
      python .github/scripts/review.py "<space separated changed files>"
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

    if list_only:
        list_models()
        return

    if bootstrap:
        if STATE_FILE.exists():
            print("Bootstrap already done; skipping.")
            return
        targets = find_unreviewed_files()
    else:
        targets = push_files

    if not targets:
        print("No targets.")
        return

    print(f"[ai-review] model: {MODEL_NAME}")
    print(f"[ai-review] targets: {len(targets)} file(s)")

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
        STATE_FILE.parent.mkdir(parents=True, exist_ok=True)
        STATE_FILE.write_text("done\n", encoding="utf-8")
        print(f"Wrote state file: {STATE_FILE}")


if __name__ == "__main__":
    main()