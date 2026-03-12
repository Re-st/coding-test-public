#include <iostream>
#include <deque>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    short n, k, tmp, zero = 0;
    int ans = 0;
    cin >> n >> k;
    deque<int> a;
    deque<short> robot;
    for (short i = 0; i < 2 * n; i++) {
        cin >> tmp;
        a.push_back(tmp);
    }
    for (;zero < k; ans++) {
        int i = a.back();
        a.pop_back();
        a.push_front(i);
        short len = robot.size();
        while (len--) {
            short r = robot.back();
            robot.pop_back();
            // move with belt and drop off
            if (++r == n - 1) continue;
            // move self
            if (a[r + 1] and (robot.empty() or robot.front() != r + 1)) {
                if (!--a[++r])
                    zero++;
                if (r == n - 1)
                    continue;
            }
            robot.push_front(r);
        }
        if (a[0]) {
            robot.push_front(0);
            if (!--a[0])
                zero++;
        }
    }
    cout << ans;

    return 0;
}