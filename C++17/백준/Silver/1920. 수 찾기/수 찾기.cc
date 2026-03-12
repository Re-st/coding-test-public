#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
static vector<int> is;

bool exists(int key, int a, int b) {
    if (a > b) return false;
    int m = (a + b) / 2;
    if (is[m] > key) return exists(key, a, m - 1);
    else if (is[m] < key) return exists(key, m + 1, b);
    else return true;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n;
    cin >> n;
    is = vector<int>(n);
    for (int i = 0; i < n; i++) {
        cin >> is[i];
    }
    sort(is.begin(), is.end());
    int m;
    cin >> m;
    int now;
    while (m--) {
        cin >> now;
        if (exists(now, 0, n - 1)) cout << "1\n"; else cout << "0\n";
    }
    return 0;
}