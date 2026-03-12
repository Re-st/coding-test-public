#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;
vector <long long> vec;
short height;

// change vec[idx] to val
void Switch(int idx, long long val) {
    vec[idx] = val;
    for (int h = height - 1; h >= 0; h--) {
        idx /= 2;
        vec[idx] = vec[2 * idx] + vec[2 * idx + 1];
    }
}

// @return: sum of vec[start:end + 1]
long long Sum(int start, int end) {
    if (start > end)
        return 0;
    long long ans = 0;
    if (start % 2)
        ans += vec[start++];
    if (!(end % 2))
        ans += vec[end--];
    return ans + Sum(start / 2, end / 2);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, m, k, a, b, operations;
    long long c;
    cin >> n >> m >> k;
    height = 0;
    while ((1 << height) < n)
        height++;
    vec.resize(1 << (height + 1));
    for (int i = (1 << height); i < (1 << height) + n; i++)
        cin >> vec[i];
    for (int h = height - 1; h >= 0; h--)
        for (int i = (1 << h); i < (1 << (h + 1)); i++)
            vec[i] = vec[2 * i] + vec[2 * i + 1];
    operations = m + k;
    while (operations--) {
        cin >> a >> b >> c;
        if (a == 1)
            Switch(b + (1 << height) - 1, c);
        else
            cout << Sum(b + (1 << height) - 1, (int) c + (1 << height) - 1) << '\n';
    }
    return 0;
}