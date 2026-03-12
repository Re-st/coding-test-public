#include <iostream>
#include <vector>

using namespace std;
vector<vector<int>> T;
int parent[100001][21];
int height[100001];
bool visited[100001];
int kmax;

// @returns LCA of a and b in tree T
int LCA(int a, int b, bool doneHeightCalibration) {
    if (!doneHeightCalibration) {
        int heightdiff = height[a] - height[b];
        if (heightdiff < 0) {
            swap(a, b);
            heightdiff = -heightdiff;
        }
        int k = 0;
        while (heightdiff) {
            if (heightdiff % 2)
                a = parent[a][k];
            heightdiff /= 2;
            k++;
        }
    }
    if (a == b)
        return a;
    for (int k = kmax; k >= 0 and a != b; k--) {
        if (parent[a][k] != parent[b][k]) {
            a = parent[a][k];
            b = parent[b][k];
        }
    }
    return a != b ? parent[a][0] : a;
}

void setHeightParent(int elt) {
    for (int next : T[elt]) {
        if (!visited[next]) {
            height[next] = height[elt] + 1;
            parent[next][0] = elt;
            visited[next] = true;
            setHeightParent(next);
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, m, a, b;
    cin >> n;
    T.resize(n + 1);
    kmax = 0;
    int tmp = n >> 1;
    while (tmp) {
        tmp >>= 1;
        kmax++;
    }
    for (int _i = 0; _i < n - 1; _i++) {
        cin >> a >> b;
        T[a].push_back(b);
        T[b].push_back(a);
    }
    visited[1] = true;
    setHeightParent(1);
    for (int k = 1; k <= kmax; k++) {
        for (int i = 1; i <= n; i++) {
            parent[i][k] = parent[parent[i][k - 1]][k - 1];
        }
    }
    T.clear();
    cin >> m;
    while (m--) {
        cin >> a >> b;
        cout << LCA(a, b, false) << '\n';
    }
    return 0;
}