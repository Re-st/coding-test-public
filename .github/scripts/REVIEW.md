# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `.github/scripts/review.py`

## 한 줄 결론
- (이 문제는) **[유틸리티 스크립트 / API 연동]** / 복잡도: O(F) (F=총 파일 수) / 제일 위험한 실수: 포괄적인 `except Exception`으로 인한 재시도 로직 오작동.

## 더 빠른/더 안전한 풀이(필수)
- 대안이 없으면: “현 접근이 거의 최선”
- 이유: 스크립트의 핵심 로직(파일 탐색 -> API 호출 -> 결과 저장)은 명확하며, 성능 병목은 외부 API 호출에 있어 알고리즘적 개선 여지가 적습니다. 단, 아래와 같이 안정성 및 유지보수성을 크게 높일 수 있습니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) **예외 처리**: `generate_with_retry`의 `except Exception`은 API의 일시적 오류 외에 코드 자체의 버그(e.g. `TypeError`)까지 숨기며 불필요하게 재시도할 위험이 있습니다.
- 2) **인자 파싱**: `parse_args`에서 `--files-from` 같은 플래그 뒤에 값이 없으면 `argv[i+1]` 접근 시 `IndexError`가 발생하여 스크립트가 비정상 종료됩니다.
- 3) **경로 처리 일관성**: `os.path`와 `pathlib.Path`가 혼용되어, 경로를 다루는 방식이 일관되지 않고 코드를 파악하기 어렵습니다.

## 즉시 수정 액션(최대 4개)
- 1. (`generate_with_retry`) `except Exception`을 `google.api_core.exceptions`의 특정 예외(e.g., `ResourceExhausted`)만 잡도록 구체화하세요.
- 2. (`parse_args`) 수동 인자 파싱 대신, Python 표준 라이브러리 `argparse`를 도입하여 안정성과 확장성을 확보하세요.
- 3. (`전체`) `os.path.join` 대신 `pathlib.Path`의 `/` 연산자를 일관되게 사용하여 경로 처리를 통일하세요.
- 4. (`read_readme` 등) 파일 경로를 받는 함수들이 문자열 대신 `Path` 객체를 받도록 시그니처를 변경하여 타입 일관성을 높이세요.

```REVIEW_EXAMPLE
# 제목: argparse를 이용한 견고한 인자 파싱
- 적용 조건: 스크립트의 커맨드 라인 인터페이스를 더 안정적이고 확장성 있게 만들고 싶을 때.
- 핵심 아이디어: `sys.argv`를 직접 파싱하는 대신, `argparse` 라이브러리를 사용해 인자를 선언적으로 정의하고 파싱을 위임하여 안정성과 가독성을 높입니다.
- 복잡도: 동일
- 구현 스케치(선택):
```python
import argparse
from pathlib import Path

def setup_arg_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="AI Code Reviewer")
    parser.add_argument("--bootstrap", action="store_true", help="Run on unreviewed files.")
    parser.add_argument("--list-models", action="store_true", help="List models and exit.")
    parser.add_argument("--files-from", type=Path, help="Read target file paths from a file.")
    parser.add_argument("files", nargs="*", type=Path, help="Specific files to review.")
    return parser

# main() 함수 내부에서...
# args = setup_arg_parser().parse_args()
#
# all_files = args.files
# if args.files_from:
#     if args.files_from.exists():
#         all_files.extend(Path(line.strip()) for line in args.files_from.read_text().splitlines() if line.strip())
#
# targets = sorted(set(all_files))
```
```