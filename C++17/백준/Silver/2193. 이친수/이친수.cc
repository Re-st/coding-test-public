#include <iostream>
#include <vector>

using namespace std;

#define MAX_INT 1000000001

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n;
    cin >> n;
    vector<long long> ans(n + 1);
    ans[0] = 0;
    ans[1] = 1;
    for (int i = 2; i <= n; i++)
        //  10XXXX ans[i - 1]
        //   1XXXX ans[i - 2]
        // 10XXXXX ans[i]
        // 100XXXX ans[i - 1]
        // 101XXXX ans[i - 2]
        ans[i] = ans[i - 1] + ans[i - 2];
    cout << ans[n];
    return 0;
}