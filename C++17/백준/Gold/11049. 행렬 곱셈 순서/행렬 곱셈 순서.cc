#include <iostream>

using namespace std;

int main() {
    int n;
    int sizes[501], count[500][500];
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> sizes[i - 1] >> sizes[i];
    for (int i = 0; i < n; i++)
        count[i][i] = 0;
    for (int di = 1; di < n; di++) {
        for (int i = 0; i < n - di; i++) {
            int tmp = 1 << 31 - 1;
            for (int j = i; j < i + di; j++) {
                tmp = min(tmp, count[i][j] + count[j + 1][i + di] + sizes[i] * sizes[j + 1] * sizes[i + di + 1]);
            }
            count[i][i + di] = tmp;
        }
    }
    cout << count[0][n - 1];
    return 0;
}