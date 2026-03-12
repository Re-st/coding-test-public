#include <iostream>
#include <vector>
#include <tuple>
#include <limits.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, m, a, b, c;
    cin >> n >> m;
    int A[101][101];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j)
                A[i][j] = INT_MAX;
            else
                A[i][j] = 0;

    while (m--) {
        cin >> a >> b >> c;
        A[a][b] = min(A[a][b], c);
    }

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (i != j and j != k and k != i and A[i][k] != INT_MAX and A[k][j] != INT_MAX)
                    A[i][j] = min(A[i][j], A[i][k] + A[k][j]);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            if (A[i][j] == INT_MAX)
                cout << "0 ";
            else
                cout << A[i][j] << ' ';
        cout << '\n';
    }

    return 0;
}