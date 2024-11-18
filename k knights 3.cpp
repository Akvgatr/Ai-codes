#include <bits/stdc++.h>
#include <graphics.h>
using namespace std;

vector<vector<int> > place(vector<vector<int> >& board, int i, int j) {
    int n = board.size();
    int m = board[0].size();
    vector<vector<int> > newBoard = board;
    newBoard[i][j] = 1;

    vector<pair<int, int> > moves;
    moves.push_back(make_pair(-2, -1));
    moves.push_back(make_pair(-2, 1));
    moves.push_back(make_pair(-1, -2));
    moves.push_back(make_pair(-1, 2));
    moves.push_back(make_pair(1, -2));
    moves.push_back(make_pair(1, 2));
    moves.push_back(make_pair(2, -1));
    moves.push_back(make_pair(2, 1));

    for (size_t idx = 0; idx < moves.size(); ++idx) {
        int ni = i + moves[idx].first;
        int nj = j + moves[idx].second;
        if (ni >= 0 && nj >= 0 && ni < n && nj < m) {
            newBoard[ni][nj] = -1;
        }
    }

    return newBoard;
}

void displayBoard(const vector<vector<int> >& board) {
    for (size_t row = 0; row < board.size(); ++row) {
        for (size_t col = 0; col < board[row].size(); ++col) {
            if (board[row][col] == 1) {
                setcolor(RED);
                setfillstyle(SOLID_FILL, RED);
                circle(50 * col + 25, 50 * row + 25, 20);
                floodfill(50 * col + 25, 50 * row + 25, RED);
            } else if ((row + col) % 2 == 0) {
                setfillstyle(SOLID_FILL, GREEN);
                bar(50 * col, 50 * row, 50 * col + 50, 50 * row + 50);
            } else {
                setfillstyle(SOLID_FILL, BLUE);
                bar(50 * col, 50 * row, 50 * col + 50, 50 * row + 50);
            }
        }
    }
}

void KN(vector<vector<int> >& board, int k, int row, int col, int& count) {
    if (k == 0) {
        displayBoard(board);
        count++;
        getch();
        return;
    }

    for (size_t i = row; i < board.size(); ++i) {
        for (size_t j = (i == row ? col : 0); j < board[i].size(); ++j) {
            if (board[i][j] == 0) {
                vector<vector<int> > newBoard = place(board, i, j);
                KN(newBoard, k - 1, i, j, count);
            }
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL); // Initializes graphics mode

    int n, m, k;
    cout << "Enter board size (n x m): ";
    cin >> n >> m;
    cout << "Enter number of knights: ";
    cin >> k;

    if (k > n * m / 2) {
        cout << "Invalid number of knights" << endl;
        return 0;
    }

    vector<vector<int> > board(n, vector<int>(m, 0));
    int count = 0;

    KN(board, k, 0, 0, count);

    cout << "Total configurations: " << count << endl;
    getch();
    closegraph();
    return 0;
}

