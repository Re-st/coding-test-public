#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
//#include <math.h>
//#include <ctime>
//#include <iomanip>

using namespace std;

int inner(string w1, string w2, string w3, string w4) {
    // w1, w2 hor. w3, w4 ver.
    int cnt = 0, l1 = w1.length(), l2 = w2.length(), l3 = w3.length(), l4 = w4.length();
    for (int x3 = 0; x3 < l1; x3++) {
        for (int x4 = 0; x4 < l1; x4++) {
            // distance
            if (abs(x3 - x4) < 2) continue;
            // abs(x3 - x4) >= l2 is impossible since l1 <= l2
            for (int y3 = -l3 + 1; y3 < 1; y3++) {
                // check for (x3, 0)
                if (w3[-y3] != w1[x3]) continue;
                for (int y4 = -l4 + 1; y4 < 1; y4++) {
                    // check for (x4, 0)
                    if (w4[-y4] != w1[x4]) continue;
                    for (int x2 = max(x3, x4) - l2 + 1; x2 <= min(x3, x4); x2++) {
                        for (int y2 = max(y3, y4); y2 <= min(y3 + l3 - 1, y4 + l4 - 1); y2++) {
                            // distance
                            if (abs(-y2) < 2) continue;
                            // check for (x3, y2)
                            if (w2[x3 - x2] != w3[y2 - y3]) continue;
                            // check for (x4, y2)
                            if (w2[x4 - x2] != w4[y2 - y4]) continue;
                            cnt++;
                        }
                    }
                }
            }
        }
    }
    return cnt;
}

bool shorter(string a, string b) {
    return a.length() < b.length();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    vector<string> word(4);
    for (int i = 0; i < 4; i++)
        cin >> word[i];
    // sort from shortest to longest
    sort(word.begin(), word.end(), shorter);
    int ans = 0;
    ans += inner(word[0], word[1], word[2], word[3]);
    ans += inner(word[0], word[2], word[1], word[3]);
    ans += inner(word[0], word[3], word[1], word[2]);
    cout << ans * 2 << endl;

    return 0;
}