
#include <bits/stdc++.h>
using namespace std;

const char EMPTY = ' ';
const char USER = 'X';
const char COMPUTER = 'O';

// Function to print the Tic Tac Toe board
void printBoard(const vector<vector<char>> &board)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j];
            if (j < 2)
            {
                cout << " | ";
            }
        }
        cout << endl;
        if (i < 2)
        {
            cout << "---------" << endl;
        }
    }
    cout << endl;
}

// Function to check if the board is full (draw)
bool isBoardFull(const vector<vector<char>> &board)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == EMPTY)
            {
                return false;
            }
        }
    }
    return true;
}

// Function to check if the game is over (win or draw)
bool isGameOver(const vector<vector<char>> &board, char player)
{
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
        {
            return true; // Check rows
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
        {
            return true; // Check columns
        }
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
    {
        return true; // Check diagonal (top-left to bottom-right)
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
    {
        return true; // Check diagonal (top-right to bottom-left)
    }
    return false;
}

// Function to make the computer's move
void makeComputerMove(vector<vector<char>> &board)
{
    // Check if computer can win
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == EMPTY)
            {
                board[i][j] = COMPUTER;
                if (isGameOver(board, COMPUTER))
                {
                    return; // Computer wins, no need to check other moves
                }
                board[i][j] = EMPTY; // Reset the move
            }
        }
    }

    // Check if user can win and block the user, or make a winning move
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == EMPTY)
            {
                board[i][j] = USER;
                if (isGameOver(board, USER))
                {
                    board[i][j] = COMPUTER; // Block user's winning move
                    return;
                }
                board[i][j] = COMPUTER; // Make a winning move if possible
                if (isGameOver(board, COMPUTER))
                {
                    return;
                }
                board[i][j] = EMPTY; // Reset the move
            }
        }
    }

    // If no winning move is found, make a random move
    while (true)
    {
        int row = rand() % 3;
        int col = rand() % 3;
        if (board[row][col] == EMPTY)
        {
            board[row][col] = COMPUTER;
            return;
        }
    }
}

int main()
{
    vector<vector<char>> board(3, vector<char>(3, EMPTY));
    bool userTurn = true;

    cout << "Welcome to Tic Tac Toe!" << endl;

    while (true)
    {
        cout << "Current board:" << endl;
        printBoard(board);

        if (userTurn)
        {
            int row, col;
            cout << "Enter your move (row and column): ";
            cin >> row >> col;

            if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == EMPTY)
            {
                board[row][col] = USER;
                userTurn = false;
            }
            else
            {
                cout << "Invalid move. Try again." << endl;
            }
        }
        else
        {
            cout << "Computer's turn..." << endl;
            makeComputerMove(board);
            userTurn = true;
        }

        if (isGameOver(board, USER))
        {
            cout << "Player X wins!" << endl;
            break;
        }
        else if (isGameOver(board, COMPUTER))
        {
            cout << "Player O wins!" << endl;
            break;
        }
        else if (isBoardFull(board))
        {
            cout << "It's a draw!" << endl;
            break;
        }
    }

    return 0;
}
