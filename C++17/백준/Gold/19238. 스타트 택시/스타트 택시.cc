#include <iostream>
#include <deque>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m, fuel, tmp, da, db, sa, sb, ea, eb;
bool wall[21][21];
typedef pair<int, int> dest;
dest customer[21][21];
bool isCustomer[21][21];
bool visited[21][21];
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

inline bool canGo(int a, int b) {
    return a >= 1 && a <= n && b >= 1 && b <= n && !wall[a][b] && !visited[a][b];
}

// 목적지까지 주행하는 함수
int drive(dest destination) {
    if (da == destination.first && db == destination.second) return 0;
    deque<dest> dq = { {da, db} };
    memset(visited, false, sizeof(visited));
    visited[da][db] = true;

    int dist = 0;
    while (!dq.empty()) {
        dist++;
        int sz = dq.size();
        while (sz--) {
            dest d = dq.front(); dq.pop_front();
            for (int j = 0; j < 4; j++) {
                int na = d.first + dx[j], nb = d.second + dy[j];
                if (canGo(na, nb)) {
                    if (na == destination.first && nb == destination.second) return dist;
                    visited[na][nb] = true;
                    dq.push_back({ na, nb });
                }
            }
        }
    }
    return 1e9;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> fuel;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            cin >> tmp;
            wall[i][j] = (tmp == 1);
        }
    cin >> da >> db;
    for (int i = 0; i < m; i++) {
        cin >> sa >> sb >> ea >> eb;
        customer[sa][sb] = { ea, eb };
        isCustomer[sa][sb] = true;
    }

    for (int i = 0; i < m; i++) {
        dest nextC = { 21, 21 };
        int minD = 1e9;
        bool found = false;

        // // 여기 이렇게 틀렸는데 고친거: 현재 택시 자리에 손님이 있는 경우를 BFS 밖에서 먼저 체크해야 0거리 손님을 안 놓침
        if (isCustomer[da][db]) {
            nextC = { da, db };
            minD = 0;
            found = true;
        } else {
            memset(visited, false, sizeof(visited));
            deque<dest> dq = { {da, db} };
            visited[da][db] = true;
            int dist = 0;
            while (!dq.empty() && !found) {
                dist++;
                int sz = dq.size();
                while (sz--) {
                    dest d = dq.front(); dq.pop_front();
                    for (int j = 0; j < 4; j++) {
                        int na = d.first + dx[j], nb = d.second + dy[j];
                        if (canGo(na, nb)) {
                            visited[na][nb] = true;
                            dq.push_back({ na, nb });
                            if (isCustomer[na][nb]) {
                                found = true;
                                if (na < nextC.first || (na == nextC.first && nb < nextC.second)) {
                                    nextC = { na, nb };
                                    minD = dist;
                                }
                            }
                        }
                    }
                }
            }
        }

        if (!found || fuel < minD) { cout << -1; return 0; }

        fuel -= minD;
        isCustomer[nextC.first][nextC.second] = false;
        da = nextC.first; db = nextC.second;

        dest goal = customer[nextC.first][nextC.second]; // // 여기 이렇게 틀렸는데 고친거: 목적지를 미리 변수에 담아두지 않으면 da, db가 바뀌면서 꼬일 수 있음
        int len = drive(goal);
        
        if (fuel < len || len == 1e9) { cout << -1; return 0; }

        fuel += len; 
        // // 여기 이렇게 틀렸는데 고친거: 목적지에 도착했으면 택시 위치(da, db)를 반드시 그 목적지 좌표로 갱신해야 다음 손님을 제대로 찾음
        da = goal.first; db = goal.second; 
    }

    cout << fuel;
    return 0;
}