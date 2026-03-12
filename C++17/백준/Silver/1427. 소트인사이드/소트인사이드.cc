#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    string n;
    cin >> n;
    for (int i = 0; i < n.length() - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < n.length(); j++)
            if (n[j] > n[maxIdx]) maxIdx = j;
        // swap
        int tmp = n[maxIdx];
        n[maxIdx] = n[i];
        n[i] = tmp;
    }
    cout << n;
}