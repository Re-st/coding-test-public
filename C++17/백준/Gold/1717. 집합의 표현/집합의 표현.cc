#include <iostream>
#include <vector>
using namespace std;

void Union(int, int);
int Find(int);
vector<int> parent;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, m, op, a, b;
    cin >> n >> m;
    parent.resize(n + 1);
    for (int i = 0; i <= n; i++) parent[i] = i;
    while (m--) {
        cin >> op >> a >> b;
        if (!op)
            Union(a, b);
        else if (Find(a) == Find(b))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}

void Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    parent[b] = a;
}

int Find(int a) {
    if (parent[a] == a)
        return a;
    else
        return parent[a] = Find(parent[a]);
}