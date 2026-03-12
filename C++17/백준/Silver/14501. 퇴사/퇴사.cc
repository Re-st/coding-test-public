#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n;
    cin >> n;
    vector<int> t(n), p(n), maxp(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> t[i] >> p[i];
        for (int j = 0; j < i; j++) {
            if (t[j] + j <= i) maxp[i] = max(maxp[i], maxp[j] + p[j]);
        }
    }
    for (int j = 0; j < n; j++) {
        if (t[j] + j <= n) maxp[n] = max(maxp[n], maxp[j] + p[j]);
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = max(ans, maxp[i]);
    }
    cout << ans;
    return 0;
}