#include <iostream>
#include <vector>
using namespace std;
int n, maxans = -1e9, minans = 1e9;
vector<short> a;
int o1, o2, o3, o4; // + - * /

void dfs(short depth, int cur) {
    if (depth == n) {
        maxans = max(maxans, cur);
        minans = min(minans, cur);
    }
    else {
        if (o1) {
            o1--;
            dfs(depth + 1, cur + a[depth]);
            o1++;
        }
        if (o2) {
            o2--;
            dfs(depth + 1, cur - a[depth]);
            o2++;
        }
        if (o3) {
            o3--;
            dfs(depth + 1, cur * a[depth]);
            o3++;
        }
        if (o4) {
            o4--;
            dfs(depth + 1, cur / a[depth]);
            o4++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> o1 >> o2 >> o3 >> o4;
    dfs(1, a[0]);
    cout << maxans << '\n' << minans;
    return 0;
}