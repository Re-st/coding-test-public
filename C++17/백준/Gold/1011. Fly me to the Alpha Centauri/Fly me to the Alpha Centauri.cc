#include <iostream>
#include <vector>
//#include <algorithm>
#include <map>
//#include <math.h>
//#include <ctime>
//#include <iomanip>

using namespace std;

map<int, int> dist = { {1, 1} };

int inner(int n) {
    int curspeed = 1, acc = 0;
    while (true) {
        if (n > 2 * curspeed) {
            n -= 2 * curspeed;
            curspeed++;
            acc += 2;
        }
        else if (n > curspeed) {
            acc += 2;
            break;
        }
        else {
            acc++;
            break;
        }
    }
    return acc;
}

int impl(int n) {
    if (dist.find(n) != dist.end()) {
        return dist[n];
    }
    else {
        int ans = inner(n);
        dist[n] = ans;
        return ans;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int x, y;
        cin >> x >> y;
        cout << impl(y - x) << endl;
    }
    return 0;
}