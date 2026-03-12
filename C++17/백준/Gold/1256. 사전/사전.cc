#include <iostream>
#include <vector>

using namespace std;

#define MAX_INT 1000000001

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, m, k;
    int combi[201][201];
    cin >> n >> m >> k;
    // 1'st to 0'th
    k--;
    for (int i = 0; i <= n + m; i++) {
        combi[i][0] = 1;
        combi[i][i] = 1;
    }
    for (int i = 1; i <= n + m; i++)
        for (int j = 1; j < i; j++)
            combi[i][j] = min(MAX_INT, combi[i - 1][j] + combi[i - 1][j - 1]);

    if (k >= combi[n + m][n]) {
        cout << "-1";
        return 0;
    }

    while (n or m) {
        int startsWithA = n ? combi[n + m - 1][n - 1] : 0;
        if (k < startsWithA) {
            cout << 'a';
            n--;
        }
        else {
            cout << 'z';
            m--;
            k -= startsWithA;
        }
    }
    return 0;
}