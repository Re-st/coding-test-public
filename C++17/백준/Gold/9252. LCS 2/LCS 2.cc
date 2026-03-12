#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int dp[1001][1001];

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    string s1, s2;
    cin >> s1 >> s2;

    int n1 = s1.length(), n2 = s2.length();

    for (int i = 1; i <= n1; i++) {
        for (int j = 1; j <= n2; j++) {
            if (s1[i - 1] == s2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    cout << dp[n1][n2] << "\n";

    if (dp[n1][n2] > 0) {
        string res = "";
        int i = n1, j = n2;
        while (i > 0 && j > 0) {
            if (dp[i][j] == dp[i - 1][j]) i--;
            else if (dp[i][j] == dp[i][j - 1]) j--;
            else {
                res += s1[i - 1];
                i--; j--;
            }
        }
        reverse(res.begin(), res.end());
        cout << res;
    }

    return 0;
}