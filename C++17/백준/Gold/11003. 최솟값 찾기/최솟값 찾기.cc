#include <iostream>
#include <deque>
using namespace std;
// idx, val
typedef pair<int, int> Node;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    deque<Node> mydeque;
    int n, l, tmp;
    cin >> n >> l;
    for (int ptr = 0; ptr < n; ptr++) {
        if (ptr >= l and mydeque.front().first == ptr - l)
            mydeque.pop_front();
        cin >> tmp;
        while (!mydeque.empty())
            if (mydeque.back().second >= tmp)
                mydeque.pop_back();
            else break;
        mydeque.push_back(Node(ptr, tmp));
        cout << mydeque.front().second << " ";
    }
    return 0;
}