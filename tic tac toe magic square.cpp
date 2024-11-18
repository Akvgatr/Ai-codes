#include <iostream>
#include <array>
using namespace std;





array<int, 10> grid{2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
int moves = 1;
bool playerFirst = false;  // Variable to track if player goes first










int findWinningSpot(int mark) {
    int prod;
    array<array<int, 3>, 8> winPatterns = {{
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9},
        {1, 4, 7}, {2, 5, 8}, {3, 6, 9},
        {1, 5, 9}, {3, 5, 7}
    }};

    for (const auto& pattern : winPatterns) {
        prod = grid[pattern[0]] * grid[pattern[1]] * grid[pattern[2]];
        if (prod == mark * mark * 2) {
            for (int pos : pattern) {
                if (grid[pos] == 2) return pos;
            }
        }
    }
    return 0;
}









void showGrid() {
    for (int i = 1; i < 10; i++) {
        cout << grid[i] << " ";
        if (i % 3 == 0) cout << "\n";
    }
    cout << endl;
}









bool checkWin(int mark) {
    array<array<int, 3>, 8> winPatterns = {{
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9},
        {1, 4, 7}, {2, 5, 8}, {3, 6, 9},
        {1, 5, 9}, {3, 5, 7}
    }};
    
    for (const auto& pattern : winPatterns) {
        int prod = grid[pattern[0]] * grid[pattern[1]] * grid[pattern[2]];
        if (prod == mark * mark * mark) {
            return true;  // A win condition is met
        }
    }
    return false;
}











int findAlternateSpot() {
    if (grid[5] == 2) return 5;
    for (int pos : {2, 4, 6, 8}) {
        if (grid[pos] == 2) return pos;
    }
    return -1;
}







void makeMove(int pos) {
    if (moves % 2 == 1) {
        grid[pos] = 3;  
    } else {
        grid[pos] = 5;  
    }
    moves++;
}




















void playerMove() {
    int selection;
    cout << "Enter your move (1-9): ";
    cin >> selection;

    while (selection < 1 || selection > 9 || grid[selection] != 2) {
        cout << "Invalid input! Try again: ";
        cin >> selection;
    }

    makeMove(selection);
}




void playGame() {
    while (moves <= 9) {
        showGrid();

        if (playerFirst) {
            if (moves % 2 == 1) {  // Player's turn on odd moves
                playerMove();
                if (checkWin(5)) {  // Check if the player has won
                    showGrid();
                    cout << "Player wins!" << endl;
                    return;
                }
            } else {  // Computer's turn on even moves
                switch (moves) {
                    case 2: grid[5] == 2 ? makeMove(5) : makeMove(1); break;
                    case 4: findWinningSpot(3) ? makeMove(findWinningSpot(3)) : makeMove(findAlternateSpot()); break;
                    case 6: 
                        if (findWinningSpot(5)) {
                            makeMove(findWinningSpot(5));
                        } else if (findWinningSpot(3)) {
                            makeMove(findWinningSpot(3));
                        } else {
                            makeMove(findAlternateSpot());
                        }
                        break;
                    default: 
                        if (findWinningSpot(3)) {
                            makeMove(findWinningSpot(3));
                        } else if (findWinningSpot(5)) {
                            makeMove(findWinningSpot(5));
                        } else {
                            for (int i = 1; i <= 9; i++) {
                                if (grid[i] == 2) {
                                    makeMove(i);
                                    break;
                                }
                            }
                        }
                        break;
                }
                if (checkWin(3)) {  // Check if the computer has won
                    showGrid();
                    cout << "Computer wins!" << endl;
                    return;
                }
            }
        } else {  // Computer goes first
            if (moves % 2 == 1) {  // Computer's turn on odd moves
                switch (moves) {
                    case 1: makeMove(1); break;
                    case 3: grid[9] == 2 ? makeMove(9) : makeMove(3); break;
                    case 5: 
                        if (findWinningSpot(3)) {
                            makeMove(findWinningSpot(3));
                        } else if (findWinningSpot(5)) {
                            makeMove(findWinningSpot(5));
                        } else {
                            grid[7] == 2 ? makeMove(7) : makeMove(3);
                        }
                        break;
                    default: 
                        if (findWinningSpot(3)) {
                            makeMove(findWinningSpot(3));
                        } else if (findWinningSpot(5)) {
                            makeMove(findWinningSpot(5));
                        } else {
                            for (int i = 1; i <= 9; i++) {
                                if (grid[i] == 2) {
                                    makeMove(i);
                                    break;
                                }
                            }
                        }
                        break;
                }
                if (checkWin(3)) {  // Check if the computer has won
                    showGrid();
                    cout << "Computer wins!" << endl;
                    return;
                }
            } else {  // Player's turn on even moves
                playerMove();
                if (checkWin(5)) {  // Check if the player has won
                    showGrid();
                    cout << "Player wins!" << endl;
                    return;
                }
            }
        }
    }
    showGrid();
    cout << "Game over! It's a tie!" << endl;
}





void askFirstTurn() {
    char choice;
    cout << "Do you want to go first? (y/n): ";
    cin >> choice;
    playerFirst = (choice == 'y' || choice == 'Y');
}




int main() {
    askFirstTurn();  // Ask the player if they want to go first
    playGame();
    return 0;
}

