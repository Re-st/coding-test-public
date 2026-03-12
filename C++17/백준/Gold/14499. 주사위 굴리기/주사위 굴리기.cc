#include <iostream>
#include <string.h>

using namespace std;
int n, m, y, x, curloc, k;

int map[400];

// curr dice
int upSide = 0;
int downSide = 0;
int leftSide = 0;
int rightSide = 0;
int frontSide = 0;
int backSide = 0;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m >> x >> y >> k;
    for (int i = 0; i < m * n; i++) {
        cin >> map[i];
    }

    int direction, tmp;
    for (int i = 0; i < k; i++) {
        cin >> direction;
        switch (direction) {
            case 1: // E
                if (y == m - 1) continue;
                y++;
                tmp = upSide;
                upSide = leftSide;
                leftSide = downSide;
                downSide = rightSide;
                rightSide = tmp;
                break;
            case 2: // W
                if (y == 0) continue;
                y--;
                tmp = leftSide;
                leftSide = upSide;
                upSide = rightSide;
                rightSide = downSide;
                downSide = tmp;
                break;
            case 3: // N
                if (x == 0) continue;
                x--;
                tmp = upSide;
                upSide = frontSide;
                frontSide = downSide;
                downSide = backSide;
                backSide = tmp;
                break;
            case 4: // S
                if (x == n - 1) continue;
                x++;
                tmp = frontSide;
                frontSide = upSide;
                upSide = backSide;
                backSide = downSide;
                downSide = tmp;
                break;
            default:
                break;
        }
        int tmp = map[x * m + y];
        if (tmp) {
            map[x * m + y] = 0;
            downSide = tmp;
        }
        else {
            map[x * m + y] = downSide;
        }
        cout << upSide << '\n';
    }
    return 0;
}