# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/1516. 게임 개발/게임 개발.cc`

## 한 줄 결론
- (이 문제는) **위상 정렬** / 복잡도: O(N*E) / 비효율적인 결과값 갱신 로직

## 더 빠른/더 안전한 풀이(필수)
- **아이디어**: 큐에서 노드를 꺼낼 때마다, 그 노드에서 출발하는 간선에 연결된 다음 노드의 최소 완료 시간을 점진적으로 갱신합니다.
- **복잡도**: O(N + E)
- **왜 이게 더 좋은지**: 각 간선을 한 번만 사용하여 시간 복잡도를 크게 개선하고, `Ap` 같은 불필요한 역방향 그래프 없이 구현이 더 간결해집니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점/종료조건: `indegree`가 0인 노드들의 `ans` 값을 `reqtime`으로 초기화하는 부분은 올바릅니다.
- 2) 인덱스/경계/오버플로/방문처리: N=500, 시간=10^5이므로 경로상 시간의 총합이 `int` 범위를 초과할 위험은 낮습니다.
- 3) 자료구조/성능 함정: `indegree[i]`가 0이 될 때 `Ap[i]`(i의 모든 선행자)를 순회하며 `max`를 찾는 로직이 성능 저하의 주범입니다. 이로 인해 선행 관계가 중복으로 검사됩니다.

## 즉시 수정 액션(최대 4개)
- 1. `Ap` 벡터(선행 건물 목록)를 제거하세요. 역방향 그래프는 필요 없습니다.
- 2. `ans` 갱신 로직을 `if (!--indegree[i])` 블록 밖으로 옮기세요.
- 3. `for (int i : A[a])` 루프 안에서 `ans[i] = max(ans[i], ans[a] + reqtime[i]);` 와 같이 값을 갱신해야 합니다. (`a`: 현재 노드, `i`: 다음 노드)
- 4. `indegree[i]`가 0이 되면 큐에 `i`를 넣기만 하고, `ans` 계산은 하지 마세요.

```REVIEW_EXAMPLE
# 제목: 더 빠른 위상 정렬 풀이
- 적용 조건: 현재 풀이보다 항상 시간 복잡도가 우수하며, 구현이 더 간단합니다.
- 핵심 아이디어: 큐에서 노드 `curr`를 꺼낼 때, `curr`에 의존하는 다음 노드 `next`의 완료 시간을 `result_time[next] = max(result_time[next], result_time[curr] + build_time[next])`로 갱신합니다. 모든 선행 작업이 끝났을 때 한 번에 계산하는 대신, 선행 작업이 끝날 때마다 점진적으로 갱신하여 중복 계산을 피합니다.
- 복잡도: O(N + E)
- 구현 스케치(C++):
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    vector<int> indegree(n + 1, 0);
    vector<int> build_time(n + 1);
    vector<int> result_time(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        cin >> build_time[i];
        int prereq;
        while (cin >> prereq && prereq != -1) {
            adj[prereq].push_back(i);
            indegree[i]++;
        }
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
            result_time[i] = build_time[i];
        }
    }

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (int next : adj[curr]) {
            result_time[next] = max(result_time[next], result_time[curr] + build_time[next]);
            if (--indegree[next] == 0) {
                q.push(next);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << result_time[i] << '\n';
    }

    return 0;
}
```