#include <iostream>

using namespace std;

int main() 
{
    int n;
    double m = 0, sum = 0;
    int num[1001];
    int tmp;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> num[i];
    for (int i = 0; i < n; i++) {
        tmp = num[i];
        if (tmp > m) m = tmp;
        sum += tmp;
    }
    cout << sum * 100.0 / m / n;
    return 0;
}
