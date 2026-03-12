#include <iostream>

using namespace std;
int main() {
    int n, sum = 0;
    string nstr;
    cin >> n;
    cin >> nstr;
    for (int i = 0; i < n; i++) sum += nstr[i] - '0';
    cout << sum;
    return 0;
}