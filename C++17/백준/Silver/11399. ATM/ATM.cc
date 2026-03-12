#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n;
    cin >> n;
    vector<int> pi(n);
    cin >> pi[0];
    for (int i = 1; i < n; i++) {
        int now;
        cin >> now;
        int nowLoc = 0;
        for (; nowLoc < i; nowLoc++) if (pi[nowLoc] > now) break;
        for (int j = i - 1; j >= nowLoc; j--) pi[j + 1] = pi[j];
        pi[nowLoc] = now;
    }
    int acc = 0;
    for (int i = 0; i < n; i++) acc += (n - i) * pi[i];
    cout << acc;
    return 0;
}