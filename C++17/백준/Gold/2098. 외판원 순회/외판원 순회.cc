#include <iostream>

using namespace std;

int n, W[16][16], cost[65536 * 16]; // cost -1 if not travel-able

// returns -1 if not travel-able.
int travelCost(int curr, int leftover) {

    if (cost[(curr << n) + leftover])
        return cost[(curr << n) + leftover];

    int ret;
    if (!leftover)
        ret = W[curr][0] ? W[curr][0] : -1;
    else {
        ret = 100000000;
        for (int i = 0; i < n; i++) {
            if (((1 << i) & leftover) and W[curr][i]) {
                int toAdd = travelCost(i, leftover - (1 << i));
                if (toAdd != -1)
                    ret = min(ret, W[curr][i] + toAdd);
            }
        }
    }
    return cost[(curr << n) + leftover] = (ret == 100000000) ? -1 : ret;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    // 0XXX XXXX XXXX XXXX 0, with {1, 2, 3, .., n - 1} to fill.
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> W[i][j];
        }
    }
    fill(cost, cost + (n << n), 0);
    cout << travelCost(0, (1 << n) - 2);
    return 0;
}