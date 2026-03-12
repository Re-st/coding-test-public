#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, m;
    cin >> m;
    while (m--) {
        string minStr = "", maxStr = "";
        cin >> n;
        // minStr
        int digit = (n + 6) / 7;
        switch (n % 7) {
        case 1:
            minStr += "10";
            digit -= 2;
            break;
        case 2:
            minStr += "1";
            digit--;
            break;
        case 3:
            if (digit == 1) {
                minStr += "7";
                digit = 0;
            } else if (digit == 2) {
                minStr += "22";
                digit = 0;
            } else {
                minStr += "200";
                digit -= 3;
            }
            break;
        case 4:
            if (digit == 1) {
                minStr += "4";
                digit = 0;
            }
            else {
                minStr += "20";
                digit -= 2;
            }
            break;
        case 5:
            minStr += "2";
            digit -= 1;
            break;
        case 6:
            minStr += "6";
            digit -= 1;
            break;
        case 0:
        default:
            break;
        }
        while (digit--)
            minStr += "8";
        // maxStr
        if (n % 2) {
            maxStr += "7";
            n -= 3;
        }
        while (n) {
            maxStr += "1";
            n -= 2;
        }
        cout << minStr << ' ' << maxStr << '\n';
    }
    return 0;
}