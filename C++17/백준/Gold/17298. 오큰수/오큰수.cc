#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// idx, val
typedef pair<int, int> Node;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    stack<Node> myStack;
    int n;
    cin >> n;
    vector<int> ans(n, -1);
    int now;
    for (int i = 0; i < n; i++) {
        cin >> now;
        while (!myStack.empty() and now > myStack.top().second) {
            ans[myStack.top().first] = now;
            myStack.pop();
        }
        myStack.push(Node(i, now));
    }
    for (int i = 0; i < n; i++) cout << ans[i] << ' ';
    return 0;
}