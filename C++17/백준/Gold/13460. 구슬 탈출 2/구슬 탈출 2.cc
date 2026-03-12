#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
int n, m, res = -1;
bool notfound = true;
struct LocPair {
    int red;
    int blue;
    int depth;
    LocPair(int r, int b, int d) : red(r), blue(b), depth(d) {}
};
deque<LocPair> myqueue;
int goal;

// false if wall
bool map[100] = { false }; // does it initialize every cell to false?

void move(LocPair cur, int movedist) {
    // instantly stop if blue goaled
    // move 2 balls until 1 can not move (either struck wall, or goaled)
    while (map[cur.red + movedist] and map[cur.blue + movedist]) {
        cur.red += movedist;
        cur.blue += movedist;
        if (cur.red == goal) {
            notfound = false;
            break;
        }
        else if (cur.blue == goal) {
            notfound = true;
            return;
        }
    }
    // move red ball if not goaled
    if (notfound)
        while (map[cur.red + movedist] && (cur.red + movedist != cur.blue)) {
            cur.red += movedist;
            if (cur.red == goal) {
                notfound = false;
            }
        }
    // move blue wall
    while (map[cur.blue + movedist] && ((!notfound) or cur.blue + movedist != cur.red)) {
        cur.blue += movedist;
        if (cur.blue == goal) {
            notfound = true;
            return;
        }
    }
    if (!notfound) {
        res = cur.depth + 1;
        return;
    } else {
        myqueue.emplace_back(cur.red, cur.blue, cur.depth + 1);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    char tmp;
    LocPair initial(0, 0, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> tmp;
            switch (tmp) {
                case '.':
                    map[i * 10 + j] = true;
                    break;
                case 'R':
                    map[i * 10 + j] = true;
                    initial.red = i * 10 + j;
                    break;
                case 'B':
                    map[i * 10 + j] = true;
                    initial.blue = i * 10 + j;
                    break;
                case 'O':
                    map[i * 10 + j] = true;
                    goal = i * 10 + j;
                    break;
                default:
                    break;
            }
        }
    myqueue.push_back(initial);
    while (notfound) {
        LocPair cur = myqueue.front();
        myqueue.pop_front();
        if (cur.depth == 10) break;

        move(cur, -10);
        if (notfound) move(cur, -1);
        if (notfound) move(cur, 1);
        if (notfound) move(cur, 10);
    }

    cout << res;
    return 0;
}