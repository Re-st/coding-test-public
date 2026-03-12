#include <iostream>
#include <vector>
#include <queue>
using namespace std;

short n, half;
int ans = 1e9;
short s[20][20];
deque<short> start, link;

void dfs(short idx, int startSum, int linkSum) {
    if (idx == n) {
        ans = min(ans, abs(startSum - linkSum));
    }
    else {
        if (start.size() != half) {
            int newSum = 0;
            for (short oldIdx : start) {
                newSum += s[idx][oldIdx];
                newSum += s[oldIdx][idx];
            }
            start.push_back(idx);
            dfs(idx + 1, startSum + newSum, linkSum);
            start.pop_back();
        }
        if (link.size() != half) {
            int newSum = 0;
            for (short oldIdx : link) {
                newSum += s[idx][oldIdx];
                newSum += s[oldIdx][idx];
            }
            link.push_back(idx);
            dfs(idx + 1, startSum, linkSum + newSum);
            link.pop_back();
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cin >> s[i][j];
    half = n / 2;
    dfs(0, 0, 0);
    cout << ans;
    return 0;
}