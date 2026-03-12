#include <iostream>
#include <vector>
#include <queue>
using namespace std;

static int d[500][500];
int x, y;
// line 2, sq 1, L 8, S 4, T 4
const int SHAPE_MAX = 19;
const vector<vector<pair<int, int>>> shape = {
    {{0, 1}, {0, 1}, {0, 1}},
    {{1, 0}, {1, 0}, {1, 0}}, //
    {{1, 0}, {0, 1}, {-1, 0}}, //
    {{0, 1}, {0, 1}, {1, 0}},
    {{0, 1}, {0, 1}, {-1, 0}},
    {{1, 0}, {1, 0}, {0, 1}},
    {{1, 0}, {1, 0}, {0, -1}},
    {{0, -1}, {0, -1}, {1, 0}},
    {{0, -1}, {0, -1}, {-1, 0}},
    {{-1, 0}, {-1, 0}, {0, 1}},
    {{-1, 0}, {-1, 0}, {0, -1}}, //
    {{0, 1}, {1, 0}, {0, 1}},
    {{0, 1}, {-1, 0}, {0, 1}},
    {{1, 0}, {0, 1}, {1, 0}},
    {{1, 0}, {0, -1}, {1, 0}}, //
    {{0, 1}, {0, 1}, {1, -1}},
    {{0, 1}, {0, 1}, {-1, -1}},
    {{1, 0}, {1, 0}, {-1, 1}},
    {{1, 0}, {1, 0}, {-1, -1}} //
};

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> d[i][j];
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < SHAPE_MAX; k++) {
                int cur = d[i][j];
                int curi = i, curj = j;
                bool impossible = false;
                for (int l = 0; l < 3; l++) {
                    curi += shape[k][l].first;
                    curj += shape[k][l].second;
                    if (curi < 0 or curi >= n or curj < 0 or curj >= m) {
                        impossible = true;
                        break;
                    }
                    cur += d[curi][curj];
                }
                if (!impossible) ans = max(ans, cur);
            }
        }
    cout << ans;
    return 0;
}