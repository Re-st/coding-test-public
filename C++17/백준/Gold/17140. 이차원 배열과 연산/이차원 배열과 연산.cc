#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> countType;

int d[100][100], rowsize = 3, colsize = 3, newD[100][100];

void doRCalc() {
    memset(newD, 0, sizeof(newD));
    int newColsize = 0;
    for (int i = 0; i < rowsize; i++) {
        int cnt[101] = { 0 }; // 모두 0으로 초기화되나? 2차원 배열에서도 통하나?
        for (int j = 0; j < colsize; j++)
            cnt[d[i][j]]++;
        int k = 0;
        vector<countType> counts;
        for (int j = 1; j <= 100; j++)
            if (cnt[j])
                counts.push_back({cnt[j], j});
        sort(counts.begin(), counts.end());
        for (countType cntElt : counts) {
            newD[i][k++] = cntElt.second;
            newD[i][k++] = cntElt.first;
            if (k == 100)
                break;
        }
        newColsize = max(newColsize, k);
    }
    colsize = newColsize;
    memcpy(d, newD, sizeof(newD));
}

void doCCalc() {
    memset(newD, 0, sizeof(newD));
    int newRowsize = 0;
    for (int i = 0; i < colsize; i++) {
        int cnt[101] = { 0 }; // 모두 0으로 초기화되나? 2차원 배열에서도 통하나?
        for (int j = 0; j < rowsize; j++)
            cnt[d[j][i]]++;
        int k = 0;
        vector<countType> counts;
        for (int j = 1; j <= 100; j++)
            if (cnt[j])
                counts.push_back({ cnt[j], j });
        sort(counts.begin(), counts.end());
        for (countType cntElt : counts) {
            newD[k++][i] = cntElt.second;
            newD[k++][i] = cntElt.first;
            if (k == 100)
                break;
        }
        newRowsize = max(newRowsize, k);
    }
    rowsize = newRowsize;
    memcpy(d, newD, sizeof(newD));
}

void printArray(int time) {
    return;
    cout << "Time: " << time << '\n';
    for (int i = 0; i < rowsize; i++) {
        for (int j = 0; j < colsize; j++)
            cout << d[i][j] << ' ';
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int r, c, k, time = 0;
    cin >> r >> c >> k;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> d[i][j];
    while (time != 101) {
        printArray(time);
        if (d[r - 1][c - 1] == k) {
            cout << time;
            return 0;
        }
        time++;
        if (rowsize >= colsize)
            doRCalc();
        else
            doCCalc();
    }
    cout << -1;
    return 0;
}