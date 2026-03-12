#include <iostream>
#include <queue>
using namespace std;

struct compare {
    bool operator()(int o1, int o2) {
        if (abs(o1) != abs(o2)) return abs(o1) > abs(o2);
        else return o1 > o2;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    priority_queue<int, vector<int>, compare> mydeque;
    int n, now;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> now;
        if (now) {
            mydeque.push(now);
        }
        else {
            if (mydeque.empty()) {
                cout << "0\n";
            }
            else {
                cout << mydeque.top() << '\n';
                mydeque.pop();
            }
        }
    }
    return 0;
}