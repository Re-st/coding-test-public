# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./Python/백준/Gold/1931. 회의실 배정/회의실 배정.py`

## 한 줄 결론
- **그리디 알고리즘** / 복잡도: O(N log N) / N=0 입력 시 `IndexError` 발생

## 더 빠른/더 안전한 풀이(필수)
- 현 접근이 거의 최선입니다. 종료 시간 기준 정렬을 이용한 그리디는 이 문제의 표준 최적 풀이입니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) **초기값/시작점:** `N=0`일 때 `schedules`가 비어있어 `schedules[0]` 접근 시 `IndexError`가 발생합니다.
- 2) **경계 처리:** `count = 1`로 시작하고 `range(1, n)`을 순회하는 로직은 `N >= 1`을 암묵적으로 가정하여 `N=0` 처리에 실패합니다.
- 3) **자료구조/성능 함정:** `start = min(s[0] for s in schedules)` 라인은 O(N) 비용이 들지만, 이후 코드에서 사용되지 않습니다.

## 즉시 수정 액션(최대 4개)
- 1. **(권장)** `count=0`, `last_end_time=0`으로 초기화하고, 루프가 모든 회의를 순회하도록 바꿔 `N=0` 케이스를 자연스럽게 처리하세요. (아래 예시 참고)
- 2. (대안) 코드 상단에 `if n == 0: print(0); exit()` 구문을 추가해 `N=0`을 명시적으로 처리하세요.
- 3. 불필요한 `start = min(...)` 라인을 삭제하세요.

```REVIEW_EXAMPLE
# 제목: 더 안전하고 간결한 풀이 스케치
- 적용 조건: N=0 엣지 케이스를 별도 분기 없이 처리하고 싶을 때.
- 핵심 아이디어: count와 마지막 종료 시간을 0으로 초기화하고, 정렬된 모든 회의를 순회하며 조건을 검사합니다. (시간은 음수가 아니므로 첫 회의는 항상 선택됨)
- 복잡도: O(N log N)
- 구현 스케치:
```python
schedules.sort(key=lambda x:(x[1], x[0]))

count = 0
last_end_time = 0
for start_time, end_time in schedules:
    if start_time >= last_end_time:
        count += 1
        last_end_time = end_time

print(count)
```
```