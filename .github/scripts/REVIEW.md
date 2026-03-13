# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./.github/scripts/review.py`

## 1) 요약
제출된 코드는 Gemini AI 모델을 활용하여 코드 리뷰를 자동화하는 Python 스크립트입니다. 지정된 소스 파일(C++, Python) 또는 리뷰가 없는 새 파일들을 대상으로, 문제 설명(README.md)과 코드를 조합하여 프롬프트를 생성합니다. 이후 Gemini API를 호출하여 리뷰를 받고, 그 결과를 각 소스 파일의 폴더에 `REVIEW.md` 파일로 저장하는 역할을 합니다.

- **시간 복잡도**: O(F * (L + T_api)), 여기서 F는 리뷰할 파일 수, L은 파일 크기, T_api는 API 호출 시간입니다. 주로 네트워크 I/O에 의해 성능이 결정됩니다.
- **공간 복잡도**: O(M), 여기서 M은 가장 큰 파일(코드+README)의 크기입니다.

## 2) 시간 / 공간 복잡도 점검
이 스크립트는 일반적인 알고리즘 문제 풀이가 아니므로, N에 대한 복잡도보다는 처리하는 파일의 수와 크기가 중요합니다.

- **`find_unreviewed_files`**: `os.walk`를 사용하므로 저장소의 모든 파일과 디렉토리를 순회합니다. 저장소 크기가 매우 클 경우 이 부분이 느려질 수 있지만, `--bootstrap` 모드에서만 실행되므로 일반적인 CI/CD 환경(push 기반)에서는 문제가 되지 않습니다.
- **API 호출**: 스크립트의 실행 시간은 대부분 Gemini API와의 네트워크 통신 시간에 의해 결정됩니다. 코드에서 `MAX_RETRIES`와 지수 백오프(`BACKOFF_BASE_SECONDS * (2 ** (attempt - 1))`)를 구현하여 일시적인 네트워크 오류에 강건하게 대처한 점은 매우 좋습니다.

전반적으로 CI/CD 환경에서 실행되는 자동화 스크립트로서 성능상의 큰 문제는 없을 것으로 보입니다.

## 3) 구현/버그 리스크
- **인자 파싱의 잠재적 버그**: `parse_args` 함수에서 `a.split()`을 사용하여 공백으로 구분된 파일 목록을 처리합니다. 만약 파일 경로 자체에 공백이 포함되어 있다면 (예: `"path/to/my file.py"`) 의도치 않게 경로가 분리되어 `FileNotFoundError`가 발생할 수 있습니다.
    ```python
    # [풀이 코드] 141-142 라인
    else:
        files.extend(a.split())
    ```
    GitHub Actions 등에서 변경된 파일 목록을 전달할 때, 파일 경로에 공백이 포함될 가능성을 고려하여 더 안전한 파싱 방법(예: 한 줄에 파일 하나씩 처리)을 고려하는 것이 좋습니다.

- **개별 파일 처리 실패 시 전체 중단**: 메인 루프에서 특정 파일에 대한 리뷰 생성 중 예외(예: 권한 문제, 예상치 못한 파일 형식)가 발생하면 스크립트 전체가 중단됩니다. 여러 파일을 처리하는 경우, 한 파일의 실패가 다른 파일들의 리뷰에 영향을 주지 않도록 루프 내에 `try-except` 블록을 추가하여 견고성을 높일 수 있습니다.
    ```python
    # [제안] main 함수 내 루프 수정
    for f in targets:
        try:
            with open(f, encoding="utf-8") as fp:
                code = fp.read()

            # ... (리뷰 생성 및 파일 쓰기 로직) ...

        except Exception as e:
            print(f"[ai-review] Failed to process {f}: {e}")
            # continue to the next file
    ```

## 4) 엣지 케이스 체크리스트
- **빈 입력**:
    - 리뷰할 파일이 없는 경우: `No targets.` 메시지를 출력하고 정상 종료되므로 잘 처리됩니다.
    - `README.md` 또는 소스 파일이 비어있는 경우: 코드가 비어있는 문자열을 읽어 API에 전달하게 되며, 이는 API의 동작에 따라 결과가 달라지겠지만 스크립트 자체는 오류 없이 실행됩니다.
- **파일/경로 관련**:
    - **공백이 포함된 파일명**: 3번 항목에서 지적했듯이, 커맨드 라인 인자로 받을 때 파싱에 문제가 생길 수 있습니다.
    - **읽기 권한이 없는 파일**: `open()`에서 `PermissionError`가 발생하며 현재 로직에서는 스크립트가 중단됩니다.
    - **지원하지 않는 확장자**: `build_prompt_for` 함수가 기본 프롬프트(`PROMPT_COMMON`)를 반환하도록 설계되어 있어 안전하게 처리됩니다.

## 5) 리팩토링/가독성 개선 (선택)
- **`pathlib` 일관성**: 코드 내에서 `os.path`와 `pathlib.Path`가 혼용되고 있습니다. `pathlib`은 더 현대적이고 객체 지향적인 API를 제공하므로 하나로 통일하면 가독성과 유지보수성이 향상됩니다.
    ```python
    # [현재 코드]
    import os
    from pathlib import Path
    # ...
    src = os.path.join(root, f)
    review_path = os.path.join(root, "REVIEW.md")
    
    # [개선 제안]
    from pathlib import Path
    # ...
    root_path = Path(root)
    src = root_path / f
    review_path = root_path / "REVIEW.md"
    ```
- **표준 라이브러리 활용**: 간단한 인자 파싱은 현재 코드로 충분하지만, 향후 옵션이 추가될 가능성이 있다면 Python 표준 라이브러리인 `argparse`를 사용하는 것이 더 확장성 있고 명확한 방법입니다.

## 6) 한 줄 평
API 호출 시 지수 백오프를 사용한 재시도 로직으로 안정성을 확보한 점은 훌륭하지만, 공백이 포함된 파일 경로를 인자로 받을 때 발생할 수 있는 파싱 오류는 개선이 필요해 보입니다.