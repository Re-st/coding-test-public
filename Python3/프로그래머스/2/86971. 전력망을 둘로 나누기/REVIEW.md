# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./Python3/프로그래머스/2/86971. 전력망을 둘로 나누기/전력망을 둘로 나누기.py`

## 한 줄 결론
- (이 문제는) **그래프 탐색(BFS/DFS)을 이용한 완전탐색** / 복잡도: O(N^2) / `set`을 큐처럼 사용한 비표준적 탐색 구현

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: DFS를 한 번만 실행해 각 노드의 서브트리 크기를 O(N)에 미리 계산합니다.
- 복잡도: O(N)
- 왜 이게 더 좋은지: 간선을 끊을 때마다 탐색을 반복하는 O(N^2) 방식보다 훨씬 빠릅니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점/종료조건: `answer` 초기값을 `n`으로, `cnt`를 1로 설정한 것은 올바릅니다. 문제는 없습니다.
- 2) 인덱스/경계/오버플로/방문처리: `visited[w1] = True`로 간선 절단을 구현한 방식은 동작하지만, 탐색 로직에서 특정 노드(w1)를 방문하지 않도록 명시하는 것이 더 직관적입니다.
- 3) 자료구조/성능 함정: BFS/DFS 탐색 시 `set`을 사용했습니다. `collections.deque`를 사용하는 것이 표준적이고 더 효율적입니다. (코드에 `queue 구현법?` 주석을 남기신 것을 보니 이미 인지하신 것 같네요)

## 즉시 수정 액션(최대 4개)
- BFS 구현 시 `set` 대신 `from collections import deque`를 사용해 큐로 구현하세요.
- `print` 문은 최종 제출 전에 제거하세요.
- (가독성) 탐색 로직을 별도 함수로 분리하는 것을 고려해 보세요. (예: `def bfs(start, ignored_node):`)

```REVIEW_EXAMPLE
# 제목: 더 빠른 풀이 스케치 (O(N) DFS)
- 적용 조건: 현재 풀이(O(N^2))보다 항상 우수하며 N이 클 때 특히 효과적입니다.
- 핵심 아이디어: 임의의 노드를 루트로 DFS를 한 번만 수행해, 각 노드를 루트로 하는 서브트리의 크기를 계산합니다. 그 후 각 간선을 끊었을 때의 두 그룹 크기 차이를 O(1)에 계산하여 최솟값을 찾습니다.
- 복잡도: O(N)
- 구현 스케치(Python):
```python
def solution_fast(n, wires):
    graph = [[] for _ in range(n + 1)]
    for v1, v2 in wires:
        graph[v1].append(v2)
        graph[v2].append(v1)

    # 한 번의 DFS로 각 노드의 서브트리 크기 계산
    subtree_size = [0] * (n + 1)
    # parent, children 구조를 만들거나 visited로 대체 가능
    visited = [False] * (n + 1)
    
    def count_nodes_dfs(u):
        visited[u] = True
        size = 1
        for v in graph[u]:
            if not visited[v]:
                size += count_nodes_dfs(v)
        subtree_size[u] = size
        return size

    count_nodes_dfs(1) # 1번 노드를 임의의 루트로 설정

    min_diff = n
    # 루트를 제외한 모든 노드에 대해, 부모와의 간선을 끊었을 때의 차이 계산
    for i in range(2, n + 1):
        diff = abs((n - subtree_size[i]) - subtree_size[i])
        min_diff = min(min_diff, diff)
        
    return min_diff
```
```