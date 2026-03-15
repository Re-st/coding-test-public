# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Silver/2178. 미로 탐색/미로 탐색.cc`

## 한 줄 결론
- (이 문제는) **너비 우선 탐색(BFS)** / 복잡도: O(NM log(NM)) / `set`을 이용한 방문 처리가 가장 큰 성능 병목

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: 방문 여부와 거리를 `set`과 `queue`의 `Node`에 나누어 저장하는 대신, 2차원 `int` 배열 하나로 통합 관리 (예: `dist[101][101]`)
- 복잡도: O(NM)
- 왜 이게 더 좋은지: `set`의 O(log K) 연산이 배열의 O(1) 접근으로 바뀌어 훨씬 빠르고, 코드 구조가 간결해집니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
1.  **자료구조/성능 함정**: `set<pair<int, int>>`로 방문을 확인하는 것은 N, M이 100인 격자 탐색에서 불필요하게 느립니다. 2차원 `bool` 배열이 훨씬 효율적입니다.
2.  **구현 방식**: `neighbor` 함수를 `if`문 4개로 구현하는 것보다, 방향 배열(예: `dx[]`, `dy[]`)과 루프를 사용하는 것이 더 간결하고 확장성이 좋습니다.
3.  **종료 조건**: `while(true)`는 "항상 도착할 수 있다"는 문제 조건 덕분에 동작하지만, `while(!q.empty())`로 작성하는 것이 모든 BFS 상황에 적용 가능한 안전한 표준입니다.

## 즉시 수정 액션(최대 4개)
- `set<Loc> visited`를 `bool visited[101][101] = {false,};`로 변경하여 방문 확인을 O(1)로 만드세요.
- 큐에 `pair<Loc, int>` 대신 `Loc`만 저장하고, 거리는 별도 `int dist[101][101]` 배열에 기록하세요.
- `while(true)` 루프를 `while(!myDeque.empty())`로 변경하여 안정성을 높이세요.
- `neighbor` 함수를 `dx`, `dy` 방향 배열을 사용하는 방식으로 리팩토링하는 것을 고려하세요.

```REVIEW_EXAMPLE
# 제목: 2차원 배열을 이용한 O(NM) BFS 풀이
- 적용 조건: N, M 범위가 배열로 만들 수 있을 만큼 작을 때 (N, M ≤ 100이므로 최적)
- 핵심 아이디어: `dist` 2차원 배열을 방문(visited) 여부와 거리 기록용으로 동시에 활용. 0으로 초기화 후, 방문 시 `dist[ny][nx] = dist[y][x] + 1`로 갱신.
- 복잡도: O(NM)
- 구현 스케치(C++):
```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

int n, m;
int maze[101][101];
int dist[101][101]; // 0이면 미방문, 0보다 크면 방문 및 거리
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < m; j++) {
            maze[i][j] = row[j] - '0';
        }
    }

    queue<pair<int, int>> q;
    q.push({0, 0});
    dist[0][0] = 1;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (maze[nx][ny] == 1 && dist[nx][ny] == 0) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    cout << dist[n - 1][m - 1];
    return 0;
}
```
```