#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

bool visited[50][50];
int pop[50][50];
int n, l, r, ans = 0;

typedef pair<int, int> loc;
// map<loc, vector<loc>> 은 vector가 가변형이니까 불가능하지?
vector<vector<loc>> component;

inline bool open_border(int ax, int ay, int bx, int by) {
    // <= 겹치는거 c에선 안되는데 c++은?
    return l <= abs(pop[ax][ay] - pop[bx][by]) and abs(pop[ax][ay] - pop[bx][by]) <= r;
}

bool dfs(loc cur, int parent) {
    int i = cur.first;
    int j = cur.second;
    //cout << "DFS 방문: " << i << ", " << j << " Parent: " << parent << endl;
    visited[i][j] = true;
    component[parent].push_back(cur);
    bool ret = false;
    if (0 < i and not visited[i - 1][j] and open_border(i, j, i - 1, j))
    {
        dfs({ i - 1, j }, parent);
        ret = true;
    }
    if (i < n - 1 and not visited[i + 1][j] and open_border(i, j, i + 1, j))
    {
        dfs({ i + 1, j }, parent);
        ret = true;
    }
    if (0 < j and not visited[i][j - 1] and open_border(i, j, i, j - 1))
    {
        dfs({ i, j - 1 }, parent);
        ret = true;
    }
    if (j < n - 1 and not visited[i][j + 1] and open_border(i, j, i, j + 1))
    {
        dfs({ i, j + 1 }, parent);
        ret = true;
    }
    return ret;
}

// q. 이럴 때는 adj. matrix 가 편한가 edge vector (vector<vector<int>>)혹은 edge list(vector<edge>)가 편한가? edge vector겠지? edge vector라 부르는거맞나?
int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> l >> r;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> pop[i][j];
    while (true) {
        memset(visited, false, sizeof(visited));
        //         memset(visited, false, size(visited)); 는 무엇이며 왜 오류가 나는가? (visited[0]만 초기화시키던데)
        component.clear();
        component.resize(n * n);
        // q. 여기에서 그러면 초기화 (initialize) 하면서 모든 component[i] 가 빈 vector로 선언이 되는 건가? 선언이라고 말해도 되나? 엄밀한 표현은?
        bool returnFlag = true;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (visited[i][j])
                    continue;
                if (not dfs({ i, j }, i * n + j)) {
                    component[i * n + j].clear();
                }
                else
                    returnFlag = false;
            }
        }
        if (returnFlag) {
            cout << ans;
            return 0;
        }
        ans++;
        for (int parent = 0; parent < n * n; parent++) {
            int sum = 0;
            for (loc child : component[parent])
                sum += pop[child.first][child.second];
            for (loc child : component[parent])
                pop[child.first][child.second] = (int) sum / component[parent].size();
        }
    }
    return 0;
}