# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./Python3/프로그래머스/2/42747. H－Index/H－Index.py`

## 한 줄 결론
- **정렬 후 선형 탐색** / 복잡도: O(N log N) / `answer` 변수를 인덱스와 결과값으로 혼용하는 구조

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: 인용 횟수를 카운팅 배열에 기록하고, h의 최댓값(논문 수)부터 내려오며 조건을 만족하는 첫 h를 찾습니다.
- 복잡도: O(N)
- 왜 이게 더 좋은지: O(N log N) 정렬 없이 선형 시간에 해결 가능하여 더 빠르고, h값을 직접 찾아 직관적입니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점/종료조건: `while True` 루프의 종료 조건(`answer == len(citations)`)이 루프 본문과 분리되어 있어 구조가 복잡합니다.
- 2) 인덱스/경계/오버플로/방문처리: `citations[answer]` 조회 전에 `answer`가 배열 길이를 초과하는지 먼저 검사해야 `IndexError`를 피할 수 있습니다. (현재 코드는 순서가 올바릅니다)
- 3) 자료구조/성능 함정: `answer` 변수가 인덱스이자 h값 후보로 동시에 사용되어, 코드의 의도를 파악하기 어렵고 실수를 유발할 수 있습니다.

## 즉시 수정 액션(최대 4개)
- `while True` 대신 `for i, c in enumerate(citations):` 구문을 사용해 코드를 더 명확하고 간결하게 만드세요.
- 조건문을 `if c >= i + 1:` 형태로 변경하면, `i+1`이 h값 후보가 됨을 직관적으로 알 수 있습니다.
- `answer` 변수를 매번 증가시키는 대신, 마지막으로 조건을 만족한 `i + 1` 값을 저장 후 반환하는 구조를 고려해보세요.

```REVIEW_EXAMPLE
# 제목: O(N) 계수 정렬(Counting Sort) 풀이
- 적용 조건: 논문 수(N)가 많을 때 정렬 기반 풀이보다 유리합니다. (이 문제에선 N이 작아 체감은 미미)
- 핵심 아이디어: h의 최댓값은 N(논문 수)을 넘을 수 없음에 착안, 0~N까지의 인용 횟수만 계수합니다. 이후 h를 N부터 1씩 줄여가며 'h번 이상 인용된 논문이 h편 이상'인지 누적 카운트로 확인합니다.
- 복잡도: O(N)
- 구현 스케치(선택):
```python
def solution_linear(citations):
    n = len(citations)
    counts = [0] * (n + 1)
    for c in citations:
        # h-index는 n을 넘을 수 없으므로, n 초과 인용은 n으로 취급
        counts[min(c, n)] += 1

    # h번 이상 인용된 논문 수 (누적값)
    accumulated_papers = 0
    for h in range(n, -1, -1):
        accumulated_papers += counts[h]
        if accumulated_papers >= h:
            return h
    return 0
```
```