#include <iostream>
#include <vector>
using namespace std;

void printBoard(const vector<vector<int>>& board) {
    int n = board.size();
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c)
            cout << (board[r][c] ? "Q " : ". ");
        cout << '\n';
    }
}

bool isSafe(const vector<vector<int>>& board, int row, int col) {
    int n = board.size();

    // same row (left side)
    for (int j = 0; j < col; ++j)
        if (board[row][j]) return false;

    // upper-left diagonal (skip current cell)
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
        if (board[i][j]) return false;

    // lower-left diagonal (skip current cell)
    for (int i = row + 1, j = col - 1; i < n && j >= 0; ++i, --j)
        if (board[i][j]) return false;

    return true;
}


int queenRowInCol(const vector<vector<int>>& board, int col) {
    int n = board.size();
    for (int r = 0; r < n; ++r)
        if (board[r][col]) return r;
    return -1;
}

bool solve(vector<vector<int>>& board, int col) {
    int n = board.size();
    if (col == n) return true;

    // If a queen is already placed in this column, validate and move on
    int preRow = queenRowInCol(board, col);
    if (preRow != -1) {
        if (!isSafe(board, preRow, col)) return false;
        return solve(board, col + 1);
    }

    // Try placing a queen in any row of this column
    for (int row = 0; row < n; ++row) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;
            if (solve(board, col + 1)) return true;
            board[row][col] = 0; // backtrack
        }
    }
    return false;
}

int main() {
    int n, r1, c1;
    cout << "Enter board size: ";
    cin >> n;
    cout << "Enter row (1-" << n << "): ";
    cin >> r1;
    cout << "Enter column (1-" << n << "): ";
    cin >> c1;

    --r1; --c1;
    if (r1 < 0 || r1 >= n || c1 < 0 || c1 >= n) {
        cout << "Invalid position!\n";
        return 0;
    }

    vector<vector<int>> board(n, vector<int>(n, 0));
    board[r1][c1] = 1; // pre-placed queen

    if (solve(board, 0))
        printBoard(board);
    else
        cout << "No solution exists.\n";

    return 0;
}
