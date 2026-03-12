#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    stack<int> myStack;
    vector<char> acc;
    int n;
    cin >> n;
    int now, cnt = 1;
    for (int i = 0; i < n; i++) {
        cin >> now;
        while (now >= cnt) {
            myStack.push(cnt++);
            acc.push_back('+');
        }
        if (now == myStack.top()) {
            myStack.pop();
            acc.push_back('-');
        } else {
            cout << "NO";
            return 0;
        }
    }
    for (int i = 0; i < acc.size(); i++) cout << acc[i] << '\n';
    return 0;
}