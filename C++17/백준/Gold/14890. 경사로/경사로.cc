#include <iostream>
#include <vector>
using namespace std;

short n, l;
short passable(vector<short> m) {
    short height = m[0], lastup = 0, lastdown = -100;
    for (short j = 0; j < n; j++) {
        short i = m[j];
        switch (i - height) {
        case 1:
            if (j - lastdown < 2 * l) return 0;
            if (j - lastup < l) return 0;
            lastup = j;
            height = i;
            continue;
        case -1:
            if (j - lastdown < l) return 0;
            lastdown = j;
            height = i;
            continue;
        case 0:
            continue;
        default:
            return 0;
        }
    }
    if (n - lastdown < l)
        return 0;
    else
        return 1;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> l;
    vector<vector<short>> m(n, vector<short>(n));
    vector<vector<short>> mt(n, vector<short>(n));
    for (short i = 0; i < n; i++)
        for (short j = 0; j < n; j++) {
            cin >> m[i][j];
            mt[j][i] = m[i][j];
        }
    short ans = 0;
    for (short i = 0; i < n; i++) {
        ans += passable(m[i]);
        ans += passable(mt[i]);
    }
    cout << ans;

    return 0;
}