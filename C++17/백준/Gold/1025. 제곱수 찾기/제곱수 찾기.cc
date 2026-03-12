#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

bool is_square(int x) {
    int sqrtx = sqrt(x);
    return x == sqrtx * sqrtx;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> num(n, vector<int>(m, 0)); // initialize!
    for (int i = 0; i < n; i++) {
        string tmp;
        cin >> tmp;
        for (int j = 0; j < m; j++)
            num[i][j] = tmp[j] - '0';
    }
    int ans = -1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int di = -n; di <= n; di++)
                for (int dj = -m; dj <= m; dj++) {
                    if (!di and !dj) {
                        if (is_square(num[i][j])) ans = max(ans, num[i][j]); // always do {} between if - else
                    }
                    else {
                        int c = num[i][j];
                        for (int I = i + di, J = j + dj;
                            0 <= I and I < n and 0 <= J and J < m;
                            I += di, J += dj) {
                            c = 10 * c + num[I][J];
                            if (is_square(c)) ans = max(ans, c);
                        }
                    }
                }
    cout << ans;
    return 0;
}