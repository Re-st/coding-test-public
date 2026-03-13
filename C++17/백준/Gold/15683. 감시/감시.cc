#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define L 1
#define U 2
#define R 4
#define D 8
vector<short> cctvDir[6] = {
    {},
    {L, U, R, D},
    {L + R, U + D},
    {L + U, U + R, R + D, D + L},
    {L + U + R, L + U + D, L + R + D, U + R + D},
    {L + U + R + D}
};

short n, m, minCells = 64;

typedef pair<short, short> loc;
typedef pair<loc, short> cctvTy;

// 0: blank 6: wall 1~5:cctv 7:watched
short watched(loc ij, short dir, short (*o)[8]) {
    short i = ij.first;
    short j = ij.second;
    short ans = 0;
    /*for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cout << o[i][j];*/
    if (dir & L) {
        for (int jj = j; jj >= 0; jj--) {
            if (o[i][jj] == 6)
                break;
            else if (o[i][jj] == 0)
            {
                o[i][jj] = 7;
                ans++;
            }
        }
    }
    if (dir & U) {
        for (int ii = i; ii >= 0; ii--) {
            if (o[ii][j] == 6)
                break;
            else if (o[ii][j] == 0)
            {
                o[ii][j] = 7;
                ans++;
            }
        }
    }
    if (dir & R) {
        for (int jj = j; jj < m; jj++) {
            if (o[i][jj] == 6)
                break;
            else if (o[i][jj] == 0)
            {
                o[i][jj] = 7;
                ans++;
            }
        }
    }
    if (dir & D) {
        for (int ii = i; ii < n; ii++) {
            if (o[ii][j] == 6)
                break;
            else if (o[ii][j] == 0)
            {
                o[ii][j] = 7;
                ans++;
            }
        }
    }
    return ans;
}

void dfs(vector<cctvTy> cctvs, short countCells, short (*o)[8]) {
    if (cctvs.empty()) {
        minCells = min(minCells, countCells);
        return;
    }
    else {
        cctvTy cctv = cctvs.back();
        cctvs.pop_back();
        loc ij = cctv.first;
        for (short dir : cctvDir[cctv.second]) {
            short nexto[8][8];
            memcpy(nexto, o, sizeof(nexto));
            dfs(cctvs, countCells - watched(ij, dir, nexto), nexto);
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    short o[8][8], countCells = 0;
    vector<cctvTy> cctvs;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> o[i][j];
            if (0 < o[i][j] and o[i][j] < 6)
                cctvs.push_back(cctvTy(loc(i, j), o[i][j]));
            else if (o[i][j] == 0)
                countCells++;
        }
    dfs(cctvs, countCells, o);
    cout << minCells;
    return 0;
}