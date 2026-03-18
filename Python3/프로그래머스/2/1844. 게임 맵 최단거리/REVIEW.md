# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./Python3/프로그래머스/2/1844. 게임 맵 최단거리/게임 맵 최단거리.py`

## 한 줄 결론
- (이 문제는) **BFS(너비 우선 탐색)** / 복잡도: O(N*M) / 제일 위험한 실수는 표준적이지 않은 BFS 구현 방식입니다.

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: `(행, 열, 거리)` 튜플을 `deque`에 저장하는 표준 BFS로 단일 큐를 관리합니다.
- 복잡도: O(N*M)
- 왜 이게 더 좋은지: 매번 `newdeque`를 생성/교체하는 오버헤드가 없고 코드가 간결해져 버그 가능성이 줄어듭니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점/종료조건: 만약 `n=1, m=1`인 맵이 주어진다면, 현재 코드는 0을 반환하는데, 문제의 "지나온 칸의 수" 정의에 따르면 1이 더 적절합니다. (문제 제약 상 해당 케이스는 없음)
- 2) 인덱스/경계/오버플로/방문처리: 맵에 패딩(padding)을 추가하는 방식은 경계 검사를 생략할 수 있으나, `goal` 좌표를 패딩 *전에* 계산하는 등 좌표계 관리에 주의가 필요합니다.
- 3) 자료구조/성능 함정: `while` 루프마다 `newdeque`를 생성하고, 기존 `queue`를 순회한 뒤 통째로 교체하는 방식은 표준 BFS의 `popleft`와 `append`만 사용하는 것보다 비효율적입니다.

## 즉시 수정 액션(최대 4개)
- `newdeque`를 쓰는 대신, `(x, y, distance)`를 저장하는 단일 `deque`로 표준 BFS 구조로 변경하세요.
- 1-based 인덱스와 패딩 대신, 0-based 인덱스(시작: `(0,0)`, 목표: `(n-1, m-1)`)와 명시적 경계 검사를 사용해 혼란을 줄이세요.
- `visited` 방문 처리는 큐에 원소를 추가(`append`)하는 시점에 즉시 수행해야 중복 탐색을 막습니다 (현재 코드는 이 부분은 올바릅니다).
- 불필요한 `if robot == goal:` 분기는 문제 제약 조건에 의해 필요 없으므로 삭제하는 것이 좋습니다.

```REVIEW_EXAMPLE
# 제목: 표준 BFS를 이용한 더 간결한 풀이
- 적용 조건: 가중치가 없는 그래프의 최단 경로를 찾을 때 항상 더 유리합니다.
- 핵심 아이디어: `deque`에 `(행, 열, 현재까지의 거리)` 정보를 함께 저장하고, 큐가 빌 때까지 탐색을 반복합니다.
- 복잡도: O(N*M)
- 구현 스케치:
```python
from collections import deque

def solution_alternative(maps):
    n, m = len(maps), len(maps[0])
    q = deque([(0, 0, 1)]) # (행, 열, 거리)
    visited = [[False] * m for _ in range(n)]
    visited[0][0] = True
    
    dx = [0, 0, 1, -1]
    dy = [1, -1, 0, 0]

    while q:
        x, y, dist = q.popleft()
        if x == n - 1 and y == m - 1:
            return dist
        
        for i in range(4):
            nx, ny = x + dx[i], y + dy[i]
            if 0 <= nx < n and 0 <= ny < m and not visited[nx][ny] and maps[nx][ny] == 1:
                visited[nx][ny] = True
                q.append((nx, ny, dist + 1))
                
    return -1
```
```