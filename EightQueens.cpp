#include <bits/stdc++.h>
using namespace std;

#define N 8

int board[N][N]; // The chessboard represented as a 2D array where 1s represent queens, and 0s represent empty cells.

// Function to print the current solution (board configuration).
void printSolution(int board[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf(" %d ", board[i][j]); // Print 1 for queen, 0 for an empty cell.
        printf("\n");
    }
}

// Function to check if it's safe to place a queen at a given position (row, col).
bool isSafe(int row, int col)
{
    // Check if there is a queen in the same row.
    for (int i = 0; i < col; i++)
        if (board[row][i])
            return false;

    // Check if there is a queen in the left diagonal.
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check if there is a queen in the right diagonal.
    for (int i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    // If all checks pass, it's safe to place a queen at the given position.
    return true;
}

// Recursive function to solve the 8-Queens problem.
bool solveRec(int col)
{
    // If all queens are placed (all columns are processed), a solution is found.
    if (col == N)
        return true;

    // Try placing a queen in each row of the current column.
    for (int i = 0; i < N; i++)
    {
        if (isSafe(i, col))
        {
            board[i][col] = 1; // Place a queen at (i, col).

            // Recursively try to place queens in the remaining columns.
            if (solveRec(col + 1))
                return true;

            board[i][col] = 0; // If placing a queen doesn't lead to a solution, backtrack and remove the queen.
        }
    }

    // If no safe position was found in this column, return false.
    return false;
}

// Function to solve the 8-Queens problem.
bool solve()
{
    // Start solving from the first column (column 0).
    if (solveRec(0) == false)
    {
        printf("Solution does not exist");
        return false;
    }

    // If a solution is found, print the board configuration.
    printSolution(board);
    return true;
}

// Main function
int main()
{
    solve(); // Start solving the 8-Queens problem.
    return 0;
}
