# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./Python3/프로그래머스/1/42576. 완주하지 못한 선수/완주하지 못한 선수.py`

## 한 줄 결론
- **[정렬 후 비교]** / 복잡도: O(N log N) / 마지막 원소가 정답인 경우의 인덱스 경계 처리가 핵심.

## 더 빠른/더 안전한 풀이(필수)
- **아이디어**: 해시맵(`dict` 또는 `collections.Counter`)으로 참가자 이름별 인원수를 센 뒤, 완주자 명단으로 차감합니다.
- **복잡도**: O(N)
- **왜 이게 더 좋은지**: 더 빠르고(O(N) vs O(N log N)), 문제의 핵심 의도('해시')에 더 부합하는 풀이입니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) **종료 조건**: 참가자(`participant`)가 완주자(`completion`)보다 1명 많으므로, 루프가 완주자 목록 길이를 초과하는 경우를 반드시 처리해야 합니다.
- 2) **인덱스 경계**: `completion[i]` 접근 시 `IndexError`가 발생할 수 있습니다. `i >= len(completion)` 조건이 이를 막아주지만, `zip`을 쓰면 더 안전합니다.
- 3) **자료구조/성능**: 동명이인이 있으므로 단순 `set` 차집합은 쓸 수 없습니다. 현재 정렬 기반 접근은 통과되지만, 해시맵이 정석적인 O(N) 풀이입니다.

## 즉시 수정 액션(최대 4개)
- **(가독성)** `for i, answer in enumerate(participant)`의 루프 변수 `answer`를 `p_name` 등으로 바꿔 혼동을 줄이세요.
- **(간결성)** `zip`을 활용하면 인덱스 직접 관리가 불필요해져 코드가 더 깔끔하고 안전해집니다.
  ```python
  for p, c in zip(participant, completion):
      if p != c:
          return p
  return participant[-1]
  ```
- **(정리)** 맨 처음 `answer = ''`는 사용되지 않으므로 삭제하세요.

```REVIEW_EXAMPLE
# 제목: 해시맵(Counter)을 이용한 O(N) 풀이
- 적용 조건: 입력 크기가 매우 커서 O(N log N) 정렬 시간도 줄이고 싶을 때.
- 핵심 아이디어: Counter로 참가자 명단을 카운팅하고, 완주자 명단으로 빼면 최종적으로 1개만 남습니다.
- 복잡도: O(N)
- 구현 스케치(Python):
```python
import collections

def solution(participant, completion):
    # 1. participant의 각 이름별 등장 횟수를 센다.
    # 예: {"mislav": 2, "stanko": 1, "ana": 1}
    p_counter = collections.Counter(participant)

    # 2. completion 명단에 있는 이름들의 카운트를 1씩 뺀다.
    # 예: {"mislav": 1, "stanko": 0, "ana": 0}
    p_counter.subtract(collections.Counter(completion))
    
    # 3. 카운트가 1인 사람을 찾아서 반환한다.
    # most_common(1)은 [('mislav', 1)] 형태의 리스트를 반환
    return p_counter.most_common(1)[0][0]
```
```