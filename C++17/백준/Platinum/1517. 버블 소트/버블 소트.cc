#include <iostream>
#include <vector>
using namespace std;
static int ai[500001];
static int tmp[500001];

long long mergesort(int s, int e) {
    if (s >= e) return 0;
    int p1 = s, mid = (e + s) / 2, p2 = mid + 1, aiIdx = s;
    long long acc = mergesort(s, mid) + mergesort(mid + 1, e);
    for (int i = s; i <= e; i++) tmp[i] = ai[i];
    while (p1 <= mid and p2 <= e)
        if (tmp[p1] <= tmp[p2])
            ai[aiIdx++] = tmp[p1++];
        else
        {
            acc += mid + 1 - p1;
            ai[aiIdx++] = tmp[p2++];
        }
    while (p1 <= mid) ai[aiIdx++] = tmp[p1++];
    while (p2 <= e) ai[aiIdx++] = tmp[p2++];
    return acc;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> ai[i];
    cout << mergesort(0, n - 1);
    return 0;
}