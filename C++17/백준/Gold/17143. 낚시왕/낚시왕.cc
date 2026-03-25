#include <iostream>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

typedef pair<int, int> moveType;
typedef pair<moveType, int> sdz;

const int dr[] = { 0, -1, 1, 0, 0 };
const int dc[] = { 0, 0, 0, 1, -1 };
int R, C, M, totalCatchSize, verticalTravelTime, horizontalTravelTime;
sdz shark[101][101], newShark[101][101];

void fillSharks() {
    int r, c, s, d, z;
    while (M--) {
        cin >> r >> c >> s >> d >> z;
        shark[r][c] = { {s, d}, z };
    }
}

#define BLANK_SDZ sdz {{0, 0}, 0} // 여기에 sdz를 써줘야 하는 이유는? 이게 pair<int, int> 써주는것처럼 초기화할때 도움이 되나? 초기화라는 표현이 맞나?
void catchShark(int fisher) {
    for (int i = 1; i <= R; i++) {
        if (shark[i][fisher] != BLANK_SDZ) {
            totalCatchSize += shark[i][fisher].second;
            shark[i][fisher] = BLANK_SDZ;
            break;
        }
    }
    return;
}

void moveSharks() {
    fill(*newShark, *newShark + 101 * 101, BLANK_SDZ); // 잘 작동하나?
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++)
            if (shark[i][j] != BLANK_SDZ) { // 만약 struct를 쓴다면 BLANK_SDZ 대신 어떻게 써야 할까?
                int r = i, c = j, s = shark[i][j].first.first, d = shark[i][j].first.second, z = shark[i][j].second;
                switch (d) {
                case 1:
                    r = ((r - s) % verticalTravelTime + verticalTravelTime - 1) % verticalTravelTime + 1;
                    if (r > R) {
                        r = 2 * R - r;
                        d = 2;
                    }
                    break;
                case 2:
                    r = ((r + s) % verticalTravelTime + verticalTravelTime - 1) % verticalTravelTime + 1;
                    if (r > R) {
                        r = 2 * R - r;
                        d = 1;
                    }
                    break;
                case 3:
                    c = (((c + s) % horizontalTravelTime) + horizontalTravelTime - 1) % horizontalTravelTime + 1;
                    if (c > C) {
                        c = 2 * C - c;
                        d = 4;
                    }
                    break;
                case 4:
                default:
                    c = (((c - s) % horizontalTravelTime) + horizontalTravelTime - 1) % horizontalTravelTime + 1;
                    if (c > C) {
                        c = 2 * C - c;
                        d = 3;
                    }
                    break;
                }
                if (newShark[r][c].second < z)
                    newShark[r][c] = { {s, d}, z };
            }
    memcpy(shark, newShark, sizeof(shark));
    return;
}

void printSharks(string str) { // 이런거 자동으로 쉽게 만드는법 없나?
    return;
    cout << '\n' << str << '\n'; // formatting 쉬운 방법 없나
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++) {
            int s = shark[i][j].first.first, d = shark[i][j].first.second, z = shark[i][j].second;
            if (not z) continue;
            cout << "(" << i << ", " << j << ") s : " << s << ", d: " << d << ", z: " << z << '\n';
        }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> R >> C >> M;
    verticalTravelTime = 2 * (R - 1);
    horizontalTravelTime = 2 * (C - 1);
    fillSharks();
    printSharks("initial sharks");
    for (int fisher = 1; fisher <= C; fisher++) {
        catchShark(fisher);
        printSharks("catch complete");
        moveSharks();
        printSharks("move complete");
    }
    cout << totalCatchSize;
    return 0;
}