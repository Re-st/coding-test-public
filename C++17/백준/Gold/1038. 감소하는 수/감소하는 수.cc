#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int combination(int n, int r) {
    if (r == 0 or r == n) return 1;
    else return combination(n - 1, r) + combination(n - 1, r - 1);
}

int get_num(int n, int len, int acc) {

    if (len == 1) return acc + n;
    int largest_digit = len - 1;
    for (;;largest_digit++) {
        int combi_for_digit = combination(largest_digit, len - 1);
        //cout << largest_digit << " " << combi_for_digit << endl;
        if (n < combi_for_digit) break;
        n -= combi_for_digit;
    }
    acc += largest_digit * pow(10, len - 1);
    return get_num(n, len - 1, acc);

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, ans, len;
    cin >> n;
    if (n == 0) {
        cout << 0;
        return 0;
    }
    for (len = 1;len < 10; len++) {
        int combi_for_len = combination(9, len) + combination(9, len - 1);
        //cout << "combi_for_len" << combi_for_len << endl;
        if (n < combi_for_len) break;
        n -= combi_for_len;
    }
    if (len == 10) {
        if (!n) {
            cout << "9876543210";
        }
        else {
            cout << -1;
        }
        return 0;
    }
    //cout << n << " " << len << endl;
    cout << get_num(n, len, 0);
    return 0;
}