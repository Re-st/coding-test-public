#include <iostream>
#include <queue>
#include <set>
using namespace std;
// x, y, depth
typedef pair<int, int> Loc;
typedef pair<Loc, int> Node;

static int n, m;
static vector<vector<bool>> maze;

vector<Loc> neighbor(Loc loc) {
    vector<Loc> ret;
    int x = loc.first, y = loc.second;
    if (loc.first < n and maze[x + 1][y]) ret.push_back(Loc(x + 1, y));
    if (loc.first > 1 and maze[x - 1][y]) ret.push_back(Loc(x - 1, y));
    if (loc.second < m and maze[x][y + 1]) ret.push_back(Loc(x, y + 1));
    if (loc.second > 1 and maze[x][y - 1]) ret.push_back(Loc(x, y - 1));
    return ret;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    deque<Node> myDeque = { {{1, 1}, 1}};
    set<Loc> visited = { {1, 1} };

    maze = vector<vector<bool>>(n + 1, vector<bool>(m + 1, false));
    for (int i = 1; i <= n; i++) {
        string row;
        cin >> row;
        for (int j = 1; j <= m; j++) {
            maze[i][j] = (row[j - 1] == '1');
        }
    }
    while (true) {
        Node toPop = myDeque.front();
        myDeque.pop_front();
        for (Loc loc : neighbor(toPop.first)) {
            // skip if visited
            if (visited.count(loc) != 0) continue;
            // return if finished
            if (loc == Loc(n, m)) {
                cout << toPop.second + 1;
                return 0;
            }
            myDeque.push_back(Node(loc, toPop.second + 1));
            visited.insert(loc);
        }

    }
}