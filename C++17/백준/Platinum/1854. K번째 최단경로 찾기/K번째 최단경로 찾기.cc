#include <iostream>
#include <vector>
#include <queue>

using namespace std;
// weight, index
typedef pair<int, int> edge;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, m, k, a, b, c;
    cin >> n >> m >> k;
    vector<vector<edge>> A(n + 1);
    // keep each ans[i]'s size up to k.
    vector<priority_queue<int>> ans(n + 1);
    priority_queue<edge, vector<edge>, greater<edge>> pq;
    while (m--) {
        cin >> a >> b >> c;
        A[a].push_back({c, b});
    }
    pq.push({ 0, 1 });
    ans[1].push(0);
    while (!pq.empty()) {
        edge a = pq.top();
        pq.pop();
        for (edge b : A[a.second]) {
            int new_dist = b.first + a.first;
            if (ans[b.second].size() < k) {
            }
            else if (ans[b.second].top() > new_dist) {
                ans[b.second].pop();
            }
            else
                continue;
            ans[b.second].push(new_dist);
            pq.push({ new_dist, b.second });
        }
    }
    for (int i = 1; i <= n; i++) {
        if (ans[i].size() < k)
            cout << "-1\n";
        else
            cout << ans[i].top() << '\n';
    }
    return 0;
}