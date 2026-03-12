#include <iostream>
#include <vector>
using namespace std;

static char d[10001];
int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, b, c;
    cin >> n;
    long long ans = n;
    vector<int> a(n);
    while (n--) cin >> a[n];
    cin >> b >> c;
    for (int pop : a) {
        ans += ((max(0, pop - b) + c - 1) / c);
    }
    cout << ans;
    return 0;
}