#include <iostream>
#include <vector>
#include <algorithm> // needed for swap. please note.

using namespace std;

int n, m, h;
bool lad[31][11];

inline bool collide(int a, int b) {
    return lad[a][b] or lad[a][b - 1] or lad[a][b + 1];
}

bool all_identical() {
    vector<int> res(n + 1);
    for (int j = 1; j <= n; j++)
        res[j] = j;
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j < n; j++) {
            if (lad[i][j]) {
                swap(res[j], res[j + 1]);
            }
        }
    }
    for (int j = 1; j < n; j++)
        if (res[j] != j)
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m >> h;
    int a, b, ans = -1;
    while (m--) {
        cin >> a >> b;
        lad[a][b] = true;
    }
    if (all_identical()) {
        cout << 0;
        return 0;
    }
    for (int a1 = 1; a1 <= h; a1++ )
        for (int b1 = 1; b1 < n; b1++) {
            if (collide(a1, b1))
                continue;
            lad[a1][b1] = true;
            if (all_identical()) { // don't need (). please investigate
                cout << 1;
                return 0;
            }
            for (int a2 = a1; a2 <= h; a2++)
                for (int b2 = 1; b2 < n; b2++) {
                    if (collide(a2, b2))
                        continue;
                    lad[a2][b2] = true;
                    if (all_identical()) {
                        //cout << a1 << ' ' << b1 << ' ' << a2 << ' ' << b2 << '\n';
                        ans = 2;
                    }
                    if (ans != 2)
                        for (int a3 = a2; a3 <= h; a3++)
                            for (int b3 = 1; b3 < n; b3++) {
                                if (collide(a3, b3))
                                    continue;
                                lad[a3][b3] = true;
                                if (all_identical()) {
                                    ans = 3;
                                }
                                lad[a3][b3] = false;
                            }
                    lad[a2][b2] = false;
                }
            lad[a1][b1] = false;
        }
    cout << ans;
    return 0;
}