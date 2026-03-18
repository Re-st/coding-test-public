#include <iostream>
#include <set>

using namespace std;

bool visited[101][101];
int n, ans;

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };

typedef pair<int, int> loc;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    ans = 0;
    cin >> n;
    while (n--) {
        int x, y, d, g;
        cin >> x >> y >> d >> g;
        loc startpt = { x, y };
        loc endpt = { x + dx[d], y + dy[d] };
        set<loc> shape = { startpt, endpt };
        while (g--) {
            set<loc> newshape = {};
            for (loc pt : shape) {
                newshape.insert({ endpt.first + (endpt.second - pt.second), endpt.second - (endpt.first - pt.first) });
            }
            endpt = { endpt.first + (endpt.second - startpt.second), endpt.second - (endpt.first - startpt.first) };
            // custom way to print endpt?
            // cout << endpt.first << endpt.second << '\n';
            for (loc pt : newshape)
                shape.insert(pt);
// how to merge 2 vectors or sets?
        }
        for (loc pt : shape)
            visited[pt.first][pt.second] = true;
    }
    // how to chnage var name in visual studio?
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            ans += visited[i][j] and visited[i][j + 1] and visited[i + 1][j] and visited[i + 1][j + 1] ? 1 : 0;
    cout << ans;
    return 0;
}