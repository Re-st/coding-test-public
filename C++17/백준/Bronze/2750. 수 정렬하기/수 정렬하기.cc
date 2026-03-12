#include <iostream>
#include <vector>
using namespace std;


int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n;
    cin >> n;
    vector<int> myvec(n);
    while (n--) cin >> myvec[n];
    for (int i = 1; i < myvec.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (myvec[i] < myvec[j]) {
                int tmp = myvec[j];
                myvec[j] = myvec[i];
                myvec[i] = tmp;
            }
        }
    }
    for (int i = 0; i < myvec.size(); i++) cout << myvec[i] << '\n';
    return 0;
}