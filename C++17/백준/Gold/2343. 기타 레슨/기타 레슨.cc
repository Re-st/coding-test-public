#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
static vector<int> is;
static int n, m;

bool fits(int mSize) {
    int leftBluray = m, leftSpace = 0;
    for (int currClip = 0; currClip < n; currClip++) {
        int currSize = is[currClip];
        if (leftSpace < currSize) {
            if (!(leftBluray--)) return false;
            leftSpace = mSize - currSize;
        }
        else leftSpace -= currSize;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    is = vector<int>(n);
    int total = 0, maxClip = 0;
    for (int i = 0; i < n; i++) {
        cin >> is[i];
        maxClip = max(maxClip, is[i]);
        total += is[i];
    }
    int mMin = max(maxClip, (int) ceil(total / m)), mMax = total;
    while (mMin < mMax) {
        int middle = (mMin + mMax) / 2;
        if (fits(middle)) mMax = middle;
        else mMin = middle + 1;
    }
    cout << mMin;
    return 0;
}