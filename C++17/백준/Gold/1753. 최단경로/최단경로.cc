#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> edge;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int V, e, k, u, v, w;
    cin >> V >> e >> k;
    vector<vector<edge>> A(V + 1);
    vector<int> ans(V + 1, 1e9);
    vector<bool> visited(V + 1);
    priority_queue<edge, vector<edge>, greater<edge>> pq;
    while (e--) {
        cin >> u >> v >> w;
        A[u].push_back({w, v});
    }
    ans[k] = 0;
    pq.push({ 0, k });
    while (!pq.empty()) {
        edge a = pq.top();
        pq.pop();
        if (visited[a.second])
            continue;
        visited[a.second] = true;
        for (edge b : A[a.second]) {
            ans[b.second] = min(ans[b.second], ans[a.second] + b.first);
            pq.push({ ans[b.second], b.second });
        }
    }
    for (int i = 1; i <= V; i++) {
        if (ans[i] == 1e9)
            cout << "INF\n";
        else
            cout << ans[i] << '\n';
    }
    return 0;
}