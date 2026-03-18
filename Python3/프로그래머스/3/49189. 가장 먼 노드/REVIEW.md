# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./Python3/프로그래머스/3/49189. 가장 먼 노드/가장 먼 노드.py`

## 한 줄 결론
- **너비 우선 탐색(BFS)** / 복잡도: O(N^2) / `list.pop(0)` 사용으로 인한 성능 저하가 가장 위험합니다.

## 더 빠른/더 안전한 풀이(필수)
- 현 접근(BFS)이 거의 최선입니다. 다만, 큐(Queue) 자료구조로 Python 리스트가 아닌 `collections.deque`로 구현해야 O(N+E) 성능을 보장받아 시간 초과를 확실히 피할 수 있습니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 자료구조/성능 함정: `queue.pop(0)`는 O(N) 연산으로, 큐가 길어지면 심각한 성능 저하를 일으킵니다. 시간 복잡도가 O(V+E)에서 최악의 경우 O(V^2)으로 나빠집니다.
- 2) 인덱스 관리: 노드 번호(1-based)와 배열 인덱스(0-based)를 계속 변환(`elt-1`, `b-1`)하고 있어 인덱스 관련 실수가 발생하기 쉽습니다.
- 3) 변수명 혼동: `while` 루프 안에서 함수 인자로 받은 `n`을 거리 값으로 재할당하고 있어 가독성을 해치고 잠재적인 버그를 유발할 수 있습니다.

## 즉시 수정 액션(최대 4개)
- `from collections import deque`를 추가하고, `queue = deque([1])`와 `queue.popleft()`를 사용하세요.
- `while` 루프 내 `n = di[elt - 1]`을 `dist = di[elt - 1]`처럼 명확한 변수명으로 바꾸세요.
- 인접 리스트 `injub`를 만들 때 `injub[a-1].append(b-1)` 처럼 0-based 인덱스로 통일하면 코드의 일관성이 높아집니다.
- 마지막 최댓값 개수 계산은 `return di.count(max(di))` 한 줄로 간소화할 수 있습니다.

```REVIEW_EXAMPLE
# 제목: 더 빠른 풀이 스케치 (deque 활용)
- 적용 조건: 노드(N)와 간선(E) 개수가 많을 때(e.g., N > 1,000), O(N^2) 복잡도로 인한 시간 초과를 방지합니다.
- 핵심 아이디어: 큐 자료구조로 `collections.deque`를 사용하여 양쪽 끝 원소 삽입/삭제를 O(1)에 수행, BFS의 시간 복잡도를 O(N+E)로 보장합니다.
- 복잡도: O(N+E)
- 구현 스케치(Python):
```python
from collections import deque

def solution(n, edge):
    # 0-based 인덱스로 인접 리스트 통일
    adj = [[] for _ in range(n)]
    for a, b in edge:
        adj[a - 1].append(b - 1)
        adj[b - 1].append(a - 1)

    distances = [-1] * n
    # 시작 노드: 1번 -> 0번 인덱스
    queue = deque([0])
    distances[0] = 0
    
    while queue:
        curr_node = queue.popleft()
        
        for neighbor in adj[curr_node]:
            if distances[neighbor] == -1:
                distances[neighbor] = distances[curr_node] + 1
                queue.append(neighbor)
                
    max_dist = max(distances)
    return distances.count(max_dist)
```
```