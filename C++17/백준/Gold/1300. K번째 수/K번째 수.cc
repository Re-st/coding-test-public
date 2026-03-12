#include <iostream>
using namespace std;
static long long n, k;

int main() {
    cin >> n >> k;
    long long vMin = 1, vMax = n * n;
    while (vMin < vMax) {
        long long middle = (vMin + vMax) / 2;
        long long idx = 0;
        for (int i = 1; i <= min(middle, n); i++) {
            idx += min(middle / i, n);
        }
        if (idx >= k) vMax = middle;
        else vMin = middle + 1;
    }
    cout << vMin;
    return 0;
}