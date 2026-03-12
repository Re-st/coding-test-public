#include <iostream>
#include <math.h>
using namespace std;
bool m[1000001];
bool square[1000001]; // a ~ b

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    long long a, b;
    cin >> a >> b;
    for (long long i = 2; i <= sqrt(b); i++) {
        if (m[i]) continue;
        const long long ii = i * i;
        for (int tmp = i + i; tmp <= sqrt(b); tmp += i) {
            m[tmp] = true;
        }
        for (long long k = (a + ii - 1) / ii; k <= b / ii; k++) {
            square[k * ii - a] = true;
        }
    }
    int ans = 0;
    for (long long i = 0; i <= b - a; i++) {
        if (!square[i]) ans++;
    }
    cout << ans;
    return 0;
}