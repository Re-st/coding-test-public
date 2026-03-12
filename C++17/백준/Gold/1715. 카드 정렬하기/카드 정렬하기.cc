#include <iostream>
#include <queue>
using namespace std;

struct Compare {
    bool operator()(int a, int b) {
        return a > b;
    }
};
static priority_queue<int, vector<int>, Compare> is;
static long long n;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    int now;
    for (int i = 0; i < n; i++) {
        cin >> now;
        is.push(now);
    }
    int acc = 0;
    while (is.size() > 1) {
        int a = is.top();
        is.pop();
        int b = is.top();
        is.pop();
        acc += a + b;
        is.push(a + b);
    };
    cout << acc;
    return 0;
}