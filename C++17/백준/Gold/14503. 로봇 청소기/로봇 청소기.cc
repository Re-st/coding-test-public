#include <iostream>
#include <vector>
using namespace std;

const short dr[6] = { -1, 0, 1, 0, -1, 0 };
const short dc[6] = { 0, 1, 0, -1, 0, 1 };

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    short n, m, r, c, d, tmp;
    int ans = 0;
    bool cleaned[50][50] = { false }, wall[50][50] = { false };
    cin >> n >> m >> r >> c >> d;
    for (short i = 0; i < n; i++)
        for (short j = 0; j < m; j++) {
            cin >> tmp;
            if (tmp) {
                wall[i][j] = true;
                cleaned[i][j] = true;
            }
        }
    while (true) {
        if (!cleaned[r][c]) {
            cleaned[r][c] = true;
            ans++;
        }
        for (int i = 0;; i++) {
            if (i == 4) {
                if (!wall[r + dr[d + 2]][c + dc[d + 2]]) {
                    r += dr[d + 2];
                    c += dc[d + 2];
                    break;
                }
                else {
                    cout << ans;
                    return 0;
                }
            }
            else {
                d = (d + 3) % 4;
                if (!cleaned[r + dr[d]][c + dc[d]]) {
                    r += dr[d];
                    c += dc[d];
                    break;
                }
            }
        }
    }
}