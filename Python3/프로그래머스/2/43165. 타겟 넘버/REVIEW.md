# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./Python3/프로그래머스/2/43165. 타겟 넘버/타겟 넘버.py`

## 한 줄 결론
- (이 문제는) **Subset-Sum 변환 후 BFS 탐색** / 복잡도: O(2^N) / 불필요한 리스트 복사로 인한 성능 저하가 위험합니다.

## 더 빠른/더 안전한 풀이(필수)
- **아이디어**: 재귀 호출(DFS)로 각 숫자를 더하거나 빼는 모든 경우를 직접 탐색.
- **복잡도**: O(2^N)
- **왜 이게 더 좋은지**: 코드가 문제 정의와 직결되어 매우 간결하고, 복잡한 상태 관리(candidates 리스트)가 불필요해 버그 위험이 적습니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점/종료조건: `(sum(numbers) - target)`이 홀수일 때 조기 리턴하는 최적화는 훌륭하나, 전체적인 풀이 방식이 직관적인 DFS보다 복잡합니다.
- 2) 인덱스/경계/오버플로/방문처리: `trial > goal`인 경우가 가지치기 되지 않아 `candidates` 리스트가 불필요하게 커질 수 있습니다. (`< goal` 조건이 암묵적 가지치기 역할을 하나 명시적이지 않습니다.)
- 3) 자료구조/성능 함정: 루프 내 `candidates += new_cand` 연산은 매번 새로운 리스트를 생성/복사하여 성능 저하를 유발합니다. 또한, `candidates`에 중복된 부분합이 저장될 수 있어 비효율적입니다.

## 즉시 수정 액션(최대 4개)
- 현재 풀이를 유지한다면, `candidates`를 `set`으로 바꿔 중복 계산을 방지하세요.
- 현재 풀이의 성능을 개선하려면, `candidates` 리스트 대신 `collections.deque`를 사용한 BFS로 구조를 명확히 할 수 있습니다.
- 가장 추천하는 것은 코드를 5~7줄의 간결한 재귀(DFS) 풀이로 재작성하는 것입니다.

```REVIEW_EXAMPLE
# 제목: 더 간결하고 직관적인 DFS 풀이
- 적용 조건: 재귀적 구조로 문제를 쉽게 분할할 수 있을 때 유리합니다. (N=20 제약에 적합)
- 핵심 아이디어: 현재 숫자를 더하는 경우와 빼는 경우로 나누어 재귀 호출하고, 모든 숫자를 다 사용했을 때 target과 일치하는지 확인합니다.
- 복잡도: O(2^N)
- 구현 스케치(Python):
  ```python
  def solution(numbers, target):
      answer = 0
      def dfs(index, current_sum):
          nonlocal answer
          if index == len(numbers):
              if current_sum == target:
                  answer += 1
              return

          dfs(index + 1, current_sum + numbers[index]) # 현재 숫자를 더하는 경우
          dfs(index + 1, current_sum - numbers[index]) # 현재 숫자를 빼는 경우

      dfs(0, 0)
      return answer
  ```
```