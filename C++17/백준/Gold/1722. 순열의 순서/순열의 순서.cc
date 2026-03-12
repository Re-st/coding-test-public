#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, op;
    cin >> n >> op;
    vector<bool> visited(n + 1, false);
    if (op == 1) {
        long long fact_array[20] = { 1, 1 };
        for (int i = 2; i < 20; i++)
            fact_array[i] = fact_array[i - 1] * i;
        int curr;
        long long ord;
        cin >> ord;
        // 1'st to 0'th
        ord--;
        for (int i = n - 1; i; i--) {
            curr = int(ord / fact_array[i]);
            ord %= fact_array[i];
            int digit = 0;
            while (curr >= 0) {
                do
                    digit++;
                while (visited[digit]);
                curr--;
            }
            visited[digit] = true;
            cout << digit << ' ';
        }
        for (int digit = 1; ;digit++)
            if (!visited[digit]) {
                cout << digit;
                break;
            }
    }
    else {
        int curr;
        long long ord = 0;
        for (int i = n - 1; i; i--) {
            cin >> curr;
            visited[curr] = true;
            for (int j = curr - 1; j; j--)
                if (visited[j])
                    curr--;
            // 1 2 3 4 to 0 1 2 3
            curr--;
            ord += curr;
            ord *= i;
        }
        int _trash;
        cin >> _trash;
        // 0'th to 1'st
        cout << ord + 1;
    }
    return 0;
}