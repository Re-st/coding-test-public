# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `.github/scripts/review.py`

## 한 줄 결론
- (이 문제는) **I/O 바운드 스크립팅** / 복잡도: O(N * T_api) / 가장 큰 약점은 순차적 파일 처리로 인한 성능 저하.

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: `concurrent.futures`를 사용해 다수 파일에 대한 API 요청을 병렬로 처리합니다.
- 복잡도: O(N * T_api / W) (W: 병렬 워커 수). I/O 대기 시간을 겹치게 해 전체 실행 시간을 크게 줄입니다.
- 왜 이게 더 좋은지: 여러 파일을 리뷰할 때 네트워크 I/O 병목을 해결하여 압도적으로 빠릅니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 경로 의존성: `REPO_ROOT`를 `parents[2]`로 고정하면 스크립트 위치가 바뀔 때 오작동합니다. `.git` 폴더를 찾는 등 더 견고한 방식이 필요합니다.
- 2) 순차 처리 병목: 리뷰 대상 파일이 많아질수록 API 요청을 하나씩 기다리므로 전체 실행 시간이 선형적으로 증가하여 비효율적입니다.
- 3) 예외 처리: `except Exception`은 모든 예외를 동일하게 처리하여 디버깅을 어렵게 합니다. API 관련 특정 예외(e.g., `google.api_core.exceptions`)를 구분해서 처리하는 것이 좋습니다.

## 즉시 수정 액션(최대 4개)
- `concurrent.futures.ThreadPoolExecutor`를 도입하여 `review` 함수 호출을 병렬화하세요.
- 경로 처리를 `pathlib`으로 통일하고, `os.path.join`과 혼용을 피하세요.
- `REPO_ROOT` 탐색 로직을 현재 파일 위치에 의존하지 않도록 개선하세요. (예: 상위 디렉토리에서 `.git` 검색)
- API 호출부의 `except Exception`을 더 구체적인 예외 타입으로 변경하여 오류 원인 파악을 용이하게 만드세요.

```REVIEW_EXAMPLE
# 제목: 병렬 처리를 통한 리뷰 가속화
- 적용 조건: 2개 이상의 파일을 동시에 리뷰할 때 실행 시간을 크게 단축시킬 수 있습니다.
- 핵심 아이디어: `ThreadPoolExecutor`를 사용해 여러 파일에 대한 Gemini API 요청을 병렬로 보냅니다. 각 요청의 네트워크 대기 시간을 겹치게 하여 전체 실행 시간을 줄입니다.
- 복잡도: O(N * T_api / W) (N: 파일 수, T_api: 파일당 API 시간, W: 워커 수)
- 구현 스케치(Python):
```python
import concurrent.futures

def process_file(file_path: str):
    """한 파일에 대한 전체 리뷰 로직을 캡슐화"""
    try:
        # ... 기존 파일 읽기, 리뷰, 결과 저장 로직 ...
        print(f"[ai-review] 성공: {file_path}")
    except Exception as e:
        print(f"[ai-review] 실패: {file_path}, 오류: {e}")

def main():
    # ... 인수 파싱 및 대상 파일 목록(targets) 생성 ...
    targets = find_unreviewed_files() # 예시

    # ThreadPoolExecutor로 병렬 처리
    with concurrent.futures.ThreadPoolExecutor() as executor:
        # 각 파일 처리를 작업으로 제출
        future_to_file = {executor.submit(process_file, f): f for f in targets}
        for future in concurrent.futures.as_completed(future_to_file):
            # 완료된 작업의 예외 처리 (필요시)
            future.result()

    # ... 부트스트랩 완료 처리 로직 ...
```
```