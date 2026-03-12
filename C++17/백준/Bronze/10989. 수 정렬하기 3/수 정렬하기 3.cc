#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, now;
    cin >> n;
    int count[10001] = { 0 };
    while (n--) {
        cin >> now;
        count[now]++;
    }
    for (int i = 1; i <= 10000; i++)
        while (count[i]--)
            cout << i << '\n';
    return 0;
}