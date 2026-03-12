#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> Node;

bool compare(Node o1, Node o2) {
    if (o1.second != o2.second) return o1.second < o2.second;
    else return o1.first < o2.first;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, val;
    cin >> n;
    vector<Node> myvec;
    for (int i = 1; i <= n; i++) {
        cin >> val;
        myvec.push_back(Node(i, val));
    }
    sort(myvec.begin(), myvec.end(), compare);
    int maxVal = 1;
    for (int i = 0; i < n; i++) {
        maxVal = max(maxVal, myvec[i].first - i);
    }
    cout << maxVal << '\n';
    return 0;
}