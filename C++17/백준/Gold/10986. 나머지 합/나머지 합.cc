#include <iostream>
#include <vector>
using namespace std;


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m, tmp, acc = 0;
    cin >> n >> m;
    vector<long> bin(m);
    bin[0] = 1;
    while (n--) {
        cin >> tmp;
        acc = (acc + tmp) % m;
        bin[acc]++;
    }
    long ans = 0;
    while (m--) ans += bin[m] * (bin[m] - 1) / 2;
    cout << ans;
    return 0;
}