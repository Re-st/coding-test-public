#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n;
    cin >> n;

    if (n < 3) { cout << 0; return 0; }

    vector<int> mat(n);
    for (int i = n; i; i--) cin >> mat[i - 1];
    sort(mat.begin(), mat.end());

    int acc = 0;
    
    for (int i = 0; i < n; i++) {
        int val = mat[i], a = 0, b = n - 1;
        while (a < b) {
            if (a == i) a++;
            else if (b == i) b--;
            else if (mat[a] + mat[b] < val) a++;
            else if (mat[a] + mat[b] > val) b--;
            else {
                acc++; break;
            }
        }
    }
    cout << acc;
    return 0;
}