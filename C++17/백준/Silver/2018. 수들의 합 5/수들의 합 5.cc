#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n, s = 1, e = 1, acc = 0;
    cin >> n;
    int status = -n + 1; // sum - n
    while (e <= n) {
        while (status < 0) status += ++e;
        while (status > 0) status -= s++;
        if (!status) { acc++; status += ++e; }
    }
    /*if (!(n % 3)) acc++;
    if (n % 2) acc++;
    cout << ++acc;*/
    cout << acc;
    return 0;
}