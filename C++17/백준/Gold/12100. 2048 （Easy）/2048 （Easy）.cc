#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef vector<int> row;
typedef vector<row> Board;
static int n, res = 0;

Board left(Board board) {
    Board result;
    for (row board_row : board) {
        row res_row;
        int before = 0;
        for (int cur : board_row) {
            if (!cur)
                continue;
            else if (!before)
                before = cur;
            else if (before == cur) {
                res_row.push_back(cur * 2);
                before = 0;
            } else {
                res_row.push_back(before);
                before = cur;
            }
        }
        if (before) res_row.push_back(before);
        while (res_row.size() < n) res_row.push_back(0);
        result.push_back(res_row);
    }
    return result;
}

Board lrflip(Board board) {
    for (row &board_row : board)
        reverse(board_row.begin(), board_row.end());
    return board;
}

Board transpose(Board& board) {
    Board result(n);
    for (row board_row : board)
        for (int i = 0; i < n; i++)
            result[i].push_back(board_row[i]);
    return result;
}

void dfs(int remSteps, Board board) {
    if (!remSteps) {
        for (row& board_row : board)
            for (int n : board_row)
                res = max(res, n);
        return;
    }

    dfs(remSteps - 1, left(board));
    Board upBoard = transpose(board);
    dfs(remSteps - 1, left(upBoard));
    Board downBoard = lrflip(upBoard);
    upBoard.clear();
    dfs(remSteps - 1, left(downBoard));
    downBoard.clear();
    Board rightBoard = lrflip(board);
    dfs(remSteps - 1, left(rightBoard));
    return;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    Board board(n, row(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> board[i][j];
    dfs(5, board);
    cout << res;
    return 0;
}