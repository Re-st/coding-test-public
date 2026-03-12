#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    int a = 0, b = n - 1, acc = 0;
    vector<int> mat(15000);
    while (n--) cin >> mat[n];
    sort(mat.begin(), mat.begin() + b + 1);
    //for (int i = 0; i < b; i++) cout << mat[i] << endl;
    while (a < b) {
        if (mat[a] + mat[b] < m) a++;
        else if (mat[a] + mat[b] > m) b--;
        else { acc++; a++; b--; }
    }
    cout << acc;
    return 0;
}