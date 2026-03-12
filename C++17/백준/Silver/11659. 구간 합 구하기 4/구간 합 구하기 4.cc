#include <iostream>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m;
    int sum[100001];
    sum[0] = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int tmp;
        cin >> tmp;
        sum[i] = sum[i-1] + tmp;
    }
    for (int i = 0; i < m; i++) {
        int I, J;
        cin >> I >> J;
        cout << sum[J] - sum[I-1] << "\n";
    }
    return 0;
}