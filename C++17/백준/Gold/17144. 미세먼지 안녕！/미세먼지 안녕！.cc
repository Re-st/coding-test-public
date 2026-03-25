#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

typedef pair<int, int> loc;

const int dr[] = { -1, 0, 1, 0 };
const int dc[] = { 0, 1, 0, -1 };

int r, c, t, condUp = -1, condDown = -1, d[50][50];
vector<loc> airFlowUp, airFlowDown;

void spreadDust() {
    int newDust[50][50];
    memcpy(newDust, d, sizeof(d));
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) {
            if (d[i][j]) {
                for (int k = 0; k < 4; k++) {
                    int newI = i + dr[k];
                    int newJ = j + dc[k];
                    if (0 <= newI and newI < r and 0 <= newJ and newJ < c
                        and loc{ newI, newJ } != loc{ condUp, 0 }
                        and loc{ newI, newJ } != loc{ condDown, 0 }) {
                        newDust[newI][newJ] += d[i][j] / 5;
                        newDust[i][j] -= d[i][j] / 5;
                    }
                }
            }
        }
    memcpy(d, newDust, sizeof(newDust));
}

void operateConditioner(const vector<loc>& airFlow) {
    int lastAirFlowUpIdx = airFlow.size() - 1;
    for (int i = 0; i < lastAirFlowUpIdx; i++) {
        d[airFlow[i].first][airFlow[i].second] = d[airFlow[i + 1].first][airFlow[i + 1].second];
    }
    d[airFlow[lastAirFlowUpIdx].first][airFlow[lastAirFlowUpIdx].second] = 0;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> r >> c >> t;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) {
            cin >> d[i][j];
            if (d[i][j] == -1) {
                d[i][j] = 0;
                if (condUp == -1)
                    condUp = i;
            }
        }
    condDown = condUp + 1;
    for (int i = condUp - 1; i > 0; i--) // i; 는 안되고 i > 0 만 되는 이유는? 착각이지? 
        airFlowUp.push_back({ i, 0 });
    for (int j = 0; j < c; j++)
        airFlowUp.push_back({ 0, j });
    for (int i = 1; i < condUp; i++)
        airFlowUp.push_back({ i, c - 1 });
    for (int j = c - 1; j > 0; j--)
        airFlowUp.push_back({ condUp, j });
    for (int i = condDown + 1; i < r - 1; i++)
        airFlowDown.push_back({ i, 0 });
    for (int j = 0; j < c; j++)
        airFlowDown.push_back({ r - 1, j });
    for (int i = r - 2; i > condDown; i--)
        airFlowDown.push_back({ i, c - 1 });
    for (int j = c - 1; j > 0; j--)
        airFlowDown.push_back({ condDown, j });
    /*
    cout << "\nairFlowUp: ";
    for (loc air : airFlowUp) {
        cout << "(" << air.first << ", " << air.second << ") ";
    }
    cout << "\nairFlowDown: ";
    for (loc air : airFlowDown) {
        cout << "(" << air.first << ", " << air.second << ") ";
    }*/
    while (t--) {
        //cout << '\n';
        spreadDust();
        operateConditioner(airFlowUp);
        //for (int i = 0; i < r; i++) {
        //    for (int j = 0; j < c; j++)
        //        cout << d[i][j] << ' ';
        //    cout << '\n';
        //}
        //cout << '\n';
        operateConditioner(airFlowDown);
        //for (int i = 0; i < r; i++) {
        //    for (int j = 0; j < c; j++)
        //        cout << d[i][j] << ' ';
        //    cout << '\n';
        //}
    }
    int dustSum = 0;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            dustSum += d[i][j];
    cout << dustSum;

    return 0;
}