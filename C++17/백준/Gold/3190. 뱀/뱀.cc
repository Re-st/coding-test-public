#include <iostream>
#include <vector>
#include <queue>
using namespace std;

static char d[10001];
int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, k, l, int1, int2;
    char char2;
    cin >> n >> k;
    vector<vector<bool>> apple(n + 1, vector<bool>(n + 1));
    vector<vector<bool>> body(n + 1, vector<bool>(n + 1));
    queue<pair<int, int>> bodyq;
    while (k--) {
        cin >> int1 >> int2;
        apple[int2][int1] = true;
    }
    cin >> l;
    while (l--) {
        cin >> int1 >> char2;
        d[int1] = char2;
    }
    int ans = 0, direction = 0, x = 1, y = 1;
    // RDLU
    const char dx[4] = { 1, 0, -1, 0 };
    const char dy[4] = { 0, 1, 0, -1 };
    body[x][y] = true;
    bodyq.push({ x, y });
    while (++ans) {
        x += dx[direction];
        y += dy[direction];
        if (x < 1 or x > n or y < 1 or y > n) break;
        if (body[x][y]) break;
        body[x][y] = true;
        bodyq.push({ x, y });
        if (apple[x][y]) {
            apple[x][y] = false;
        }
        else {
            pair<int, int> tail = bodyq.front();
            bodyq.pop();
            body[tail.first][tail.second] = false;
        }
        if (d[ans] == 'L') direction = (direction + 3) % 4;
        else if (d[ans] == 'D') direction = (direction + 1) % 4;
    }
    cout << ans;
    return 0;
}