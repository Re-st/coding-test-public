#include <iostream>
#include <vector>

using namespace std;
vector<int> fibovec = { 0, 1 };

int fibo(int x) {
    if (x < fibovec.size()) return fibovec[x];
    else {
        int ret = fibo(x - 2) + fibo(x - 1);
        fibovec.push_back(ret);
        return ret;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        if (n == 0) {
            cout << "1 0" << endl;
        } else {
            cout << fibo(n - 1) << " " << fibo(n) << endl;
        }
    }
    return 0;
}