#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// Maximum board dimension
const int MAX_N = 12;

// 8 possible knight moves in L-shape
const int dx[8] = { 2, 1, -1, -2, -2, -1,  1,  2 };
const int dy[8] = { 1, 2,  2,  1, -1, -2, -2, -1 };

// Helper structure to represent candidate moves and their Warnsdorff degree
struct MoveCandidate {
    int r;
    int c;
    int degree;
};

// Check if square (r, c) is inside the board boundaries and unvisited (-1)
bool isValid(int r, int c, int n, int board[MAX_N][MAX_N]) {
    return (r >= 0 && r < n && c >= 0 && c < n && board[r][c] == -1);
}

// Warnsdorff's Heuristic: Count number of valid, unvisited outgoing moves from (r, c)
int getDegree(int r, int c, int n, int board[MAX_N][MAX_N]) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nr = r + dx[i];
        int nc = c + dy[i];
        if (isValid(nr, nc, n, board)) {
            count++;
        }
    }
    return count;
}

// Display the formatted board
void printBoard(int n, int board[MAX_N][MAX_N]) {
    cout << "   ";
    for (int j = 0; j < n; j++) {
        cout << setw(4) << j;
    }
    cout << endl << "   +" << string(n * 4, '-') << endl;

    for (int i = 0; i < n; i++) {
        cout << setw(2) << i << " |";
        for (int j = 0; j < n; j++) {
            cout << setw(4) << board[i][j];
        }
        cout << endl;
    }
}

// Recursive Backtracking function with Warnsdorff's Optimization
// Achieves O(N^2) tour generation by prioritizing squares with fewest outgoing moves
bool solveKnightTour(int r, int c, int moveNumber, int n, int board[MAX_N][MAX_N]) {
    // Base Case: All N^2 squares visited successfully (moves numbered 1 to N^2)
    if (moveNumber > n * n) {
        return true;
    }

    // Collect all valid candidate moves
    vector<MoveCandidate> candidates;
    for (int i = 0; i < 8; i++) {
        int nextR = r + dx[i];
        int nextC = c + dy[i];
        if (isValid(nextR, nextC, n, board)) {
            int deg = getDegree(nextR, nextC, n, board);
            candidates.push_back({nextR, nextC, deg});
        }
    }

    // Warnsdorff's Heuristic: Sort candidates in ascending order of outgoing degree
    sort(candidates.begin(), candidates.end(), [](const MoveCandidate& a, const MoveCandidate& b) {
        return a.degree < b.degree;
    });

    // Try candidates recursively
    for (const auto& nextMove : candidates) {
        board[nextMove.r][nextMove.c] = moveNumber;

        if (solveKnightTour(nextMove.r, nextMove.c, moveNumber + 1, n, board)) {
            return true;
        }

        // Backtrack: Undo move if dead end encountered
        board[nextMove.r][nextMove.c] = -1;
    }

    // All candidate moves failed from this position
    return false;
}

// Runner function to initialize and solve
void runKnightTourDemo(int n, int startR, int startC) {
    cout << "------------------------------------------------------------" << endl;
    cout << "Board Size: " << n << " x " << n << " | Starting Position: (" << startR << ", " << startC << ")" << endl;
    cout << "------------------------------------------------------------" << endl;

    if (startR < 0 || startR >= n || startC < 0 || startC >= n) {
        cout << "Error: Starting position (" << startR << ", " << startC << ") is outside the " << n << "x" << n << " board!" << endl << endl;
        return;
    }

    int board[MAX_N][MAX_N];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = -1;
        }
    }

    // First move placed at start position
    board[startR][startC] = 1;

    bool success = solveKnightTour(startR, startC, 2, n, board);

    if (success) {
        cout << "SUCCESS: Valid Knight's Tour found visiting all " << (n * n) << " squares!" << endl;
        printBoard(n, board);
    } else {
        cout << "FAILURE: No valid Knight's Tour found from starting position (" << startR << ", " << startC << ")." << endl;
    }
    cout << endl;
}

int main() {
    cout << "============================================================" << endl;
    cout << "   CS250 LAB 6: TASK 4 - KNIGHT'S TOUR BACKTRACKING         " << endl;
    cout << "============================================================" << endl << endl;

    // Test Case 1: 5x5 board from (0, 0)
    runKnightTourDemo(5, 0, 0);

    // Test Case 2: 8x8 standard board from (0, 0)
    runKnightTourDemo(8, 0, 0);

    // Test Case 3: 5x5 board from center (2, 2)
    runKnightTourDemo(5, 2, 2);

    // Test Case 4: Invalid starting point boundary test
    runKnightTourDemo(5, 5, 5);

    cout << "======================= END OF TESTS =======================" << endl;
    return 0;
}
