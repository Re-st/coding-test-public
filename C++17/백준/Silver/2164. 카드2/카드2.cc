#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    deque<int> mydeque;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        mydeque.push_back(i);
    }
    bool keepflag = false;
    int now;
    while (mydeque.size() != 1) {
        if (keepflag) {
            now = mydeque.front();
            mydeque.pop_front();
            mydeque.push_back(now);
        }
        else {
            mydeque.pop_front();
        }
        keepflag = !keepflag;
    }
    cout << mydeque.front();
    return 0;
}