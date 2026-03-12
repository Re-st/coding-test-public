#include <iostream>
#include <queue>
using namespace std;

// 2 ~ inf
static priority_queue<int, vector<int>> pos;
// -inf ~ 0
static priority_queue<int, vector<int>, greater<int>> neg;
static long long n, k;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    int now, acc = 0;
    for (int i = 0; i < n; i++) {
        cin >> now;
        if (now > 1) pos.push(now);
        else if (now < 1) neg.push(now);
        else acc += 1;
    }
    while (pos.size() > 1) {
        int a = pos.top(); pos.pop();
        int b = pos.top(); pos.pop();
        acc += a * b;
    }
    if (pos.size() == 1) acc += pos.top();
    while (neg.size() > 1) {
        int a = neg.top(); neg.pop();
        int b = neg.top(); neg.pop();
        acc += a * b;
    }
    if (neg.size() == 1) acc += neg.top();
    cout << acc;
    return 0;
}