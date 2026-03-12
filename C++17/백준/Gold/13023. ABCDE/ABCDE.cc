#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> e;
vector<bool> visited;

bool dfs(int v, int depth) {
    if (depth == 5) return true;
    visited[v] = true;
    for (int i : e[v]) if (!visited[i] and dfs(i, depth + 1)) {
        visited[v] = false;
        return true;
    }
    visited[v] = false;
    return false;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, m, tmp1, tmp2;
    cin >> n >> m;
    e.resize(n);
    visited.resize(n);
    while (m--) {
        cin >> tmp1 >> tmp2;
        e[tmp1].push_back(tmp2);
        e[tmp2].push_back(tmp1);
    }
    for (int i = 0; i < n; i++) if (dfs(i, 1)) { cout << 1; return 0; }
    cout << 0; return 0;
}