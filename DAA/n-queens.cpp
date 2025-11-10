#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void printBoard(const vector<int>& pos) {
    int n = pos.size();
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c)
            cout << (pos[c] == r ? "Q " : ". ");
        cout << '\n';
    }
}

bool isSafe(const vector<int>& pos, int col, int row) {
    for (int c = 0; c < col; ++c) {
        int r = pos[c];
        if (r == row || abs(r - row) == abs(c - col))
            return false;
    }
    return true;
}

bool solve(vector<int>& pos, int col) {
    int n = pos.size();
    if (col == n) return true;

    if (pos[col] != -1)  // pre-placed queen
        return solve(pos, col + 1);

    for (int row = 0; row < n; ++row) {
        if (isSafe(pos, col, row)) {
            pos[col] = row;
            if (solve(pos, col + 1))
                return true;
            pos[col] = -1;
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

    --r1; --c1; // convert to 0-based indexing
    if (r1 < 0 || r1 >= n || c1 < 0 || c1 >= n) {
        cout << "Invalid position!\n";
        return 0;
    }

    vector<int> pos(n, -1);
    pos[c1] = r1;

    if (solve(pos, 0))
        printBoard(pos);
    else
        cout << "No solution exists.\n";
}
