#include <iostream>
#include <string.h>

using namespace std;
int n, m, maxRes = -3, res = 0;

// false if wall
int map[64]; // does it initialize every cell to false?
int new_map[64];

bool neighbor_gassed(int x) {
    if ((x % m) and (new_map[x - 1] == 2)) return true;
    if (((x + 1) % m) and (new_map[x + 1] == 2)) return true;
    if ((x >= m) and (new_map[x - m] == 2)) return true;
    if ((x < (n - 1) * m) and (new_map[x + m] == 2)) return true;
    return false;
}

void spread() {
    memcpy(new_map, map, m * n * sizeof(int));
    bool updated = true;
    int curRes = maxRes;
    while (updated) {
        updated = false;
        for (int i = 0; i < m * n; i++) {
            // better to use a set of locs where map[loc] == 0?
            if (!new_map[i] and neighbor_gassed(i)) {
                new_map[i] = 2;
                updated = true;
                curRes--;
            }
        }
    }
    res = max(res, curRes);
    return;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m * n; i++) {
        cin >> map[i];
        if (!map[i]) maxRes++;
    }

    for (int a = 0; a < n * m; a++) {
        if (map[a]) continue;
        map[a] = 1;
        for (int b = a + 1; b < n * m; b++) {
            if (map[b]) continue;
            map[b] = 1;
            for (int c = b + 1; c < n * m; c++) {
                if (map[c]) continue;
                map[c] = 1;
                spread();
                map[c] = 0;
            }
            map[b] = 0;
        }
        map[a] = 0;
    }
    cout << res;
    return 0;
}