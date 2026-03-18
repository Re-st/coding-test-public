# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./Python3/프로그래머스/3/43163. 단어 변환/단어 변환.py`

## 한 줄 결론
- (이 문제는) **BFS(너비 우선 탐색)** / 복잡도: O(N² * L) / 제일 위험한 실수는 `for` 루프 중 `list.remove()` 호출입니다.

## 더 빠른/더 안전한 풀이(필수)
- **아이디어**: `collections.deque`와 `visited` set을 이용한 정석적인 BFS로 최단 거리를 탐색합니다.
- **복잡도**: O(N² * L) (N: 단어 수, L: 단어 길이)
- **왜 이게 더 좋은지**: `list.pop(0)`(O(N)) 대신 `deque.popleft()`(O(1))를, `list.remove()`(O(N)) 대신 `set` 조회(O(1))를 사용해 더 빠르고, 순회 중 리스트를 변경하는 버그를 원천 차단하여 안전합니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) **초기값/종료조건**: `target`이 `words`에 없는 경우 변환 불가인데, 이 처리가 코드 초반에 명시적으로 없어 실수가능성이 있습니다.
- 2) **방문처리**: `for word in words:` 루프 안에서 `words.remove(word)`를 실행하면, 일부 원소를 건너뛰는 심각한 버그가 발생할 수 있습니다. 방문 처리는 별도의 `visited` 자료구조로 해야 안전합니다.
- 3) **자료구조/성능 함정**: BFS 큐로 `list`를 사용하고 `pop(0)`을 호출하면 매번 O(N) 비용이 발생합니다. `collections.deque`의 `popleft()`는 O(1)이므로 훨씬 효율적입니다.

## 즉시 수정 액션(최대 4개)
- 1. `queue = []`를 `from collections import deque; queue = deque()`로 바꾸고 `pop(0)`을 `popleft()`로 수정하세요.
- 2. `words.remove(word)` 코드를 삭제하고, 방문 여부를 기록할 `visited = set()`을 도입하세요.
- 3. 함수 시작 시 `if target not in words: return 0`을 추가하여 변환 불가능한 경우를 먼저 처리하세요.
- 4. `try-except` 블록 대신 `return di.get(target, 0)`을 사용하면 더 간결하고 Pythonic합니다.

```REVIEW_EXAMPLE
# 제목: 정석 BFS를 이용한 안전한 풀이
- 적용 조건: 현재 풀이의 버그 및 성능 문제를 모두 해결하므로 항상 유리합니다.
- 핵심 아이디어: `collections.deque`를 큐로, `set`을 방문 기록용으로 사용하여 최단 경로를 찾습니다. 순회 중 원본 리스트를 변경하지 않아 안전합니다.
- 복잡도: O(N² * L)

- 구현 스케치:
  ```python
  from collections import deque

  def is_convertible(word1, word2):
      # 두 단어가 한 글자 차이인지 확인
      return sum(1 for c1, c2 in zip(word1, word2) if c1 != c2) == 1

  def solution(begin, target, words):
      if target not in words:
          return 0

      q = deque([(begin, 0)])  # (현재 단어, 변환 횟수)
      visited = {begin}

      while q:
          current_word, dist = q.popleft()

          if current_word == target:
              return dist

          for next_word in words:
              if next_word not in visited and is_convertible(current_word, next_word):
                  visited.add(next_word)
                  q.append((next_word, dist + 1))
      
      return 0 # target에 도달하지 못한 경우
  ```
```