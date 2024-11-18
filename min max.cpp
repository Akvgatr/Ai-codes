#include <iostream>
#include <vector>
#include <limits>
#include <climits>  // Added for INT_MIN
using namespace std;

vector<int> board(9, 2);
int User = 3;
int Computer = 5;
int turn = 1;
bool userFirst = true;
int maxDepth = 8;  // Default maximum depth for minimax

void display() {
    for (int i = 0; i < 9; i++) {
        if (i == 3 || i == 6) cout << endl;
        cout << (board[i] == User ? "X " : (board[i] == Computer ? "O " : "- "));
    }
    cout << endl;
}

int checkWin(const vector<int>& board, int player) {
    for (int i = 0; i < 3; i++) {
        if ((board[i * 3] == player && board[i * 3 + 1] == player && board[i * 3 + 2] == player) ||
            (board[i] == player && board[i + 3] == player && board[i + 6] == player)) {
            return 20;
        }
    }
    if ((board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player)) {
        return 20;
    }
    return 0;
}

bool isDraw() {
    for (int i = 0; i < 9; i++) {
        if (board[i] == 2) return false;
    }
    return true;
}

int rate(const vector<int>& board, int player) {
    int score = 0;

    if (player == Computer) {
        score += (board[4] == Computer) ? 10 : 0;  // Center control for Computer
        int corners[] = {0, 2, 6, 8};
        for (int i = 0; i < 4; i++) {
            if (board[corners[i]] == Computer) score += 3;  // Corner control for Computer
        }
    } else if (player == User) {
        score -= (board[4] == User) ? 10 : 0;  // Center control for User
        int corners[] = {0, 2, 6, 8};
        for (int i = 0; i < 4; i++) {
            if (board[corners[i]] == User) score -= 3;  // Corner control for User
        }
    }
    return score;
}

vector<int> moves_left(const vector<int>& board) {
    vector<int> moves;
    for (int i = 8; i >= 0; i--) {
        if (board[i] == 2) {
            moves.push_back(i);
        }
    }
    return moves;
}

int minimax(vector<int>& board, int depth, bool isComputerTurn) {
    if (depth >= maxDepth) return rate(board, Computer);  // Limit the depth

    int userWin = checkWin(board, User);
    int computerWin = checkWin(board, Computer);
    if (userWin == 10) return -10;  
    if (computerWin == 10) return 10;  
    if (isDraw()) return 0;

    int bestScore = INT_MIN;
    vector<int> moves = moves_left(board);

    for (int move : moves) {
        board[move] = isComputerTurn ? Computer : User;
        int score = -minimax(board, depth + 1, !isComputerTurn);  // Negate score for opponent's turn
        board[move] = 2;  // Undo the move
        bestScore = max(bestScore, score);
    }
    return bestScore;
}

void computerTurn() {
    vector<int> moves = moves_left(board);
    int bestScore = INT_MIN;
    int toMove = -1;

    for (int move : moves) {
        board[move] = Computer;
        int score = minimax(board, 0, false);
        board[move] = 2;  // Undo the move

        if (score > bestScore) {
            bestScore = score;
            toMove = move;
        }
    }

    if (toMove != -1) {
        board[toMove] = Computer;
    }
    display();
}

void userTurn() {
    int n;
    while (true) {
        cout << "Enter the  number for your move (1-9): ";
        cin >> n;
        if (n >= 1 && n <= 9 && board[n - 1] == 2) {
            board[n - 1] = User;
            break;
        } else {
            cout << "nivalid move" << endl;
        }
    }
}

int main() {
    cout << "enter max depth for computer search : ";
    cin >> maxDepth;

    cout << "Enter 1 to play first and 2 for second: ";
    int choice;
    cin >> choice;
    if (choice == 2) userFirst = false;

    while (turn <= 9) {
        display();
        if ((turn % 2 == 1 && userFirst) || (turn % 2 == 0 && !userFirst)) {
            userTurn();
        } else {
            cout << endl << "Computer's move:" << endl;
            computerTurn();
        }

        int userResult = checkWin(board, User);
        int computerResult = checkWin(board, Computer);
        if (userResult == 10) {
            display();
            cout << "User wins!" << endl;
            break;
        } else if (computerResult == 10) {
            display();
            cout << "Computer wins!" << endl;
            break;
        } else if (isDraw()) {
            display();
            cout << " draw!" << endl;
            break;
        }
        turn++;
    }
    return 0;
}#include <bits/stdc++.h>
using namespace std;

void printBoard(const vector<int>& board) {
    for (int i = 0; i < 9; ++i) {
        if (board[i] == 3) cout << "X ";
        else if (board[i] == 5) cout << "O ";
        else cout << ". ";
        if (i % 3 == 2) cout << endl;
    }
}

int Check_Win(const vector<int>& board) {
    vector<vector<int>> lines = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // Columns
        {0, 4, 8}, {2, 4, 6}              // Diagonals
    };

    for (auto& line : lines) {
        int a = line[0], b = line[1], c = line[2];
        if (board[a] == board[b] && board[b] == board[c]) {
            if (board[a] == 3) return 10; 
            else if (board[a] == 5) return -10;
        }
    }
    return 0;  // No win or loss
}

bool isDraw(const vector<int>& board) {
    for (int cell : board)
        if (cell == 2) 
            return false;
    return true;
}

vector<vector<int>> moveGen(const vector<int>& board, int player) 
{
    vector<vector<int>> moves;
    for (int i = 0; i < 9; ++i) {
        if (board[i] == 2) {  
            vector<int> newBoard = board;
            newBoard[i] = player;
            moves.push_back(newBoard);
        }
    }
    return moves;
}

int Static_Evaluation(const vector<int>& board, int currentPlayer) 
{
    int score = 0;
    int opponent = (currentPlayer == 3) ? 5 : 3;

    vector<vector<int>> lines = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // Columns
        {0, 4, 8}, {2, 4, 6}              // Diagonals
    };

    for (const auto& line : lines) 
    {
        int countPlayer = 0, countOpponent = 0, empty = 0;

        for (int pos : line) 
        {
            if (board[pos] == currentPlayer) countPlayer++;
            else if (board[pos] == opponent) countOpponent++;
            else empty++;
        }

        if (countOpponent == 2 && empty == 1) {
            score -= 100;  
        }

        if (countPlayer == 2 && empty == 1) {
            score += 50; 
        }

        if (countPlayer == 1 && empty == 2) score += 10;  
        if (countOpponent == 1 && empty == 2) score -= 10;  
    }

    return score;
}


int minimax(vector<int> board, int depth, int maxDepth, int player) 
{
    int score = Check_Win(board);

    if (score != 0 || depth == maxDepth || isDraw(board))
        return score + Static_Evaluation(board,player);

    int bestVal = INT_MIN;
    int opponent = (player == 3) ? 5 : 3;

    for (vector<int> move : moveGen(board, player)) {
        int newVal = -minimax(move, depth + 1, maxDepth, opponent);
        bestVal = max(bestVal, newVal);
    }
    return bestVal;
}

vector<int> ComputerMove(vector<int> board, int maxDepth, int player) 
{
    vector<int> bestBoard = board;
    int bestValue = INT_MIN;
    int opponent = (player == 3) ? 5 : 3;

    for (vector<int> move : moveGen(board, player)) 
    {
        int moveVal = -minimax(move, 1, maxDepth, opponent);

        if (moveVal > bestValue) 
        {
            bestValue = moveVal;
            bestBoard = move;
        }
    }

    return bestBoard;
}

int main() {
    vector<int> board(9, 2);  // Initialize empty board
    int maxDepth;
    string firstPlayerStr;
    int currentPlayer, userPlayer, computerPlayer;

    cout << "Enter maximum search depth for MiniMax: ";
    cin >> maxDepth;

    cout << "Who plays first? (Computer or User): ";
    cin >> firstPlayerStr;

    if (firstPlayerStr == "Computer" || firstPlayerStr == "computer") {
        computerPlayer = 3;  // X
        userPlayer = 5;      // O
        currentPlayer = computerPlayer;
    } else {
        userPlayer = 3;      // X
        computerPlayer = 5;  // O
        currentPlayer = userPlayer;
    }

    bool isPlayerTurn = (currentPlayer == userPlayer);

    while (true) {
        printBoard(board);

        int score = Check_Win(board);
        if (score == 10) {
            cout << "Player X wins!" << endl;
            break;
        } else if (score == -10) {
            cout << "Player O wins!" << endl;
            break;
        } else if (isDraw(board)) {
            cout << "It's a draw!" << endl;
            break;
        }

        if (isPlayerTurn) {
            int choice;
            cout << "Choose a position (1-9): ";
            cin >> choice;
            choice--;
            if (choice >= 0 && choice < 9 && board[choice] == 2) {
                board[choice] = currentPlayer;
                currentPlayer = (currentPlayer == 3) ? 5 : 3;
                isPlayerTurn = !isPlayerTurn;
            } else {
                cout << "Invalid move. Try again." << endl;
            }
        } else {
            cout << "Computer is making a move..." << endl;
            board = ComputerMove(board, maxDepth, currentPlayer);
            currentPlayer = (currentPlayer == 3) ? 5 : 3;
            isPlayerTurn = !isPlayerTurn;
        }
    }return 0  ;}
        
        
