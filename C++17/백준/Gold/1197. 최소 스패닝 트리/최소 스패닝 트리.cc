#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;
typedef pair<int, pair<int, int>> edge;
int parent[10001];

int Find(int a) {
    if (a == parent[a])
        return a;
    else
        return parent[a] = Find(parent[a]);
}

bool Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if (a == b)
        return false;
    else {
        parent[b] = parent[a];
        return true;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, m, a, b, c, ans = 0;
    priority_queue<edge, vector<edge>, greater<edge>> pq;
    cin >> n >> m;
    while (m--) {
        cin >> a >> b >> c;
        pq.push({ c, {a, b} });
        pq.push({ c, {b, a} });
    }
    for (int i = 1; i <= n; i++)
        parent[i] = i;
    n = n - 1;
    while (n) {
        edge e = pq.top();
        pq.pop();
        if (Union(e.second.first, e.second.second)) {
            ans += e.first;
            n--;
        }
    }

    cout << ans;
    return 0;
}