#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <limits.h>

using namespace std;

int n, m, ans;

typedef pair<int, int> loc;
vector<loc> house;
vector<loc> chicken;
int dist[100][13];

inline int chickenDistance(loc a, loc b) {
    return abs(a.first - b.first) + abs(a.second - b.second); // a.second + b.second 로 잘못씀;;
}

void dfs(int idx, int left, set<int> acc) {
    // acc gets copied in here, right?
    acc.insert(idx);
    if (left == 0) {
        //for (int j : acc)
        //    cout << j << ' ';
        //cout << '\n';
        int cityDist = 0;
        for (int i = 0; i < house.size(); i++) {
            int houseDist = INT_MAX;
            for (int j : acc) {
                houseDist = min(houseDist, dist[i][j]);
            }
            cityDist += houseDist;
        }
        ans = min(ans, cityDist);
    }
    else
        for (int i = idx + 1; i <= chicken.size() - left; i++) // 여기서 idx부터 시작하도록 실수함.;; 
            dfs(i, left - 1, acc);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    ans = INT_MAX;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int tmp;
            cin >> tmp;
            if (tmp == 1)
                house.push_back({ i, j });
            else if (tmp == 2)
                chicken.push_back({ i, j });
        }
    // does c++ have enumerate? 
    for (int i = 0; i < house.size(); i++) {
        for (int j = 0; j < chicken.size(); j++) {
            dist[i][j] = chickenDistance(house[i], chicken[j]);
            //cout << dist[i][j] << ' ';
        }
        //cout << '\n';
    }
    // was combinations able in c++? like itertools.combinations in python?
    /*vector<int> pick(chicken.size(), 0);
    fill(pick.end() - m, pick.end(), 1);
    */
    /*do {
        int cityDist = 0;
        for (int i = 0; i < house.size(); i++) {
            for (int j : pick)
        }
        ans = min(ans, cityDist);
    }*/
    //while (next_permutation(pick.begin(), pick.end()));
    set<int> emptySet = {};
    //cout << n << m << chicken.size() << '\n';
    for (int i = 0; i <= chicken.size() - m; i++)
        dfs(i, m - 1, emptySet);
    cout << ans;
    return 0;
}