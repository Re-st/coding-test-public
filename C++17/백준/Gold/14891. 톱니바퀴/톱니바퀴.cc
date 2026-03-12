#include <iostream>

using namespace std;
int t[4][8];

#define LEFT -1
#define RIGHT 1
#define BOTH 0

void move(int n, int d, int nextDir) {
    if (n < 0 or 3 < n) return;
    if (nextDir == LEFT)
        if (t[n + 1][6] == t[n][2])
            return;
    if (nextDir == RIGHT)
        if (t[n - 1][2] == t[n][6])
            return;
    switch (nextDir) {
    case LEFT:
        move(n - 1, -d, LEFT);
        break;
    case RIGHT:
        move(n + 1, -d, RIGHT);
        break;
    case BOTH:
    default:
        move(n - 1, -d, LEFT);
        move(n + 1, -d, RIGHT);
        break;
    }
    int tmp[8];
    for (int i = 0; i < 8; i++)
        tmp[i] = t[n][(i - d + 8) % 8];
    for (int i = 0; i < 8; i++)
        t[n][i] = tmp[i];
    return;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    string tmp;
    for (int i = 0; i < 4; i++) {
        cin >> tmp;
        for (int j = 0; j < 8; j++)
            t[i][j] = tmp[j] - '0';
    }
    int k;
    cin >> k;
    while (k--) {
        int n, d;
        cin >> n >> d;
        n = n - 1;
        move(n, d, BOTH);
    }
    cout << t[0][0] + 2 * t[1][0] + 4 * t[2][0] + 8 * t[3][0];
    return 0;
} 