#include <iostream>
#include <vector>
using namespace std;
static vector<int> ai;
static vector<int> tmp;

void mergesort(int s, int e) {
    if (s >= e) return;
    int p1 = s, mid = (e + s) / 2, p2 = mid + 1, aiIdx = s;
    mergesort(s, mid);
    mergesort(mid + 1, e);
    for (int i = s; i <= e; i++) tmp[i] = ai[i];
    while (p1 <= mid and p2 <= e)
        if (tmp[p1] < tmp[p2])
            ai[aiIdx++] = tmp[p1++];
        else
            ai[aiIdx++] = tmp[p2++];
    while (p1 <= mid) ai[aiIdx++] = tmp[p1++];
    while (p2 <= e) ai[aiIdx++] = tmp[p2++];
    return;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n;
    cin >> n;
    ai = vector<int>(n);
    tmp = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> ai[i];
    mergesort(0, n - 1);
    for (int i = 0; i < n; i++) cout << ai[i] << '\n';
    return 0;
}