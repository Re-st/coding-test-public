#include <iostream>
#include <vector>
#include <tuple>
#include <limits.h>

using namespace std;
// weight, index
typedef tuple<int, int, int> line;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, m, a, b, c;
    cin >> n >> m;
    long long A[501];
    vector<line> bus;
    while (m--) {
        cin >> a >> b >> c;
        bus.push_back(make_tuple(a, b, c));
    }
    A[1] = 0;
    for (int i = 2; i <= n; i++)
        A[i] = INT64_MAX;
    for (int i = 1; i < n; i++)
        for (line busline : bus) {
            a = get<0>(busline);
            b = get<1>(busline);
            c = get<2>(busline);
            if (A[a] != INT64_MAX)
                A[b] = min(A[b], A[a] + c);
        }
    for (line busline : bus) {
        a = get<0>(busline);
        b = get<1>(busline);
        c = get<2>(busline);
        if (A[a] != INT64_MAX && A[b] > A[a] + c) {
            cout << -1;
            return 0;
        }
    }
    for (int j = 2; j <= n; j++)
        if (A[j] == INT64_MAX)
            cout << "-1\n";
        else
            cout << A[j] << '\n';
    return 0;
}