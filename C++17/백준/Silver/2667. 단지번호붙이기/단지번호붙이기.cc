#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// does cpp allow funcdef inside funcdef like in python?
int n;
string board[25];
bool visited[25][25];
vector<int> danji;

void spread_danji(int i, int j) {
    if (i < 0 or i >= n or j < 0 or j >= n or visited[i][j] or board[i][j] == '0')
        return;
    visited[i][j] = true;
    danji.back() += 1;
    spread_danji(i + 1, j);
    spread_danji(i - 1, j);
    spread_danji(i, j + 1);
    spread_danji(i, j - 1);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> board[i];
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (visited[i][j] or board[i][j] == '0')
                continue;
            visited[i][j] = true;
            danji.push_back(1);
            spread_danji(i + 1, j);
            spread_danji(i - 1, j);
            spread_danji(i, j + 1);
            spread_danji(i, j - 1);
        }
    cout << danji.size() << '\n';
    sort(danji.begin(), danji.end());
    for (int d : danji)
        cout << d << '\n';
    return 0;
}