//***************************************************
// Filename: othello.c
//
// Author(s): Ummayair Ahmad, Kyle Jacobson
//***************************************************

#include "othello.h"

// Constructs and returns a string representation of the board
char *toString(int size, char board[][size]) {
    char *str = (char *) calloc(3 * (size + 1) * (size + 1), sizeof(char));
    char *ptr = str;

    for (int i = 0; i < size; i++) {
        ptr += sprintf(ptr, (i == 0 ? "%3d" : "%2d"), i + 1);
    }
    sprintf(ptr, "\n");
    ptr++;

    for (int i = 0; i < size; i++) {
        sprintf(ptr, "%1d", i + 1);
        ptr++;
        for (int j = 0; j < size; j++) {
            sprintf(ptr, "%2c", board[i][j]);
            ptr += 2;
        }
        sprintf(ptr, "\n");
        ptr++;
    }

    return str;
}

// Initializes the board with start configuration of discs (see project specs)
void initializeBoard(int size, char board[][size]) {
    // Iterate through the rows of the board.
    for (int i = 0; i < size; i++) {
        // Iterate through the columns of the board.
        for (int j = 0; j < size; j++) {
            // Empty spaces will be identified with a hyphen.
            board[i][j] = '-';
        }
    }

    // Switch used for initializing different board sizes.
    switch (size) {
        // 4x4 initial board layout.
        case 4:
            board[1][1] = 'B';
            board[2][1] = 'W';
            board[1][2] = 'W';
            board[2][2] = 'B';
            break;
            // 6x6 initial board layout.
        case 6:
            board[2][2] = 'B';
            board[3][2] = 'W';
            board[2][3] = 'W';
            board[3][3] = 'B';
            break;
            // 8x8 initial board layout.
        case 8:
            board[3][3] = 'B';
            board[4][3] = 'W';
            board[3][4] = 'W';
            board[4][4] = 'B';
            break;
    }
}

// Returns the opponentDisc disc color regarding the current player.
char getOpponentDisc(char disc) {
    // If player "Black" is currently playing, return "White".
    if (disc == 'B') {
        return 'W';
    }

    // If player "White" is currently playing, return "Black".
    else {
        return 'B';
    }
}

// Returns true if moving the disc to location row, col is valid; false otherwise.
bool isValidMove(int size, char board[][size], int row, int col, char disc) {
    // Represents the opponent's disc color regarding the current player.
    char opponentDisc = getOpponentDisc(disc);

    // If the current move is out of range on the board, return false.
    if (row > size || col > size || row < 0 || col < 0) {
        return false;
    }

    // If the current space is occupied by a disc, return false.
    if (board[row][col] != '-') {
        return false;
    }

    // Checks if adjacent space is occupied by opponent.
    if (board[row][col - 1] == opponentDisc) {
        // Iterates through the left spaces.
        for (int i = col - 2; i >= 0; i--) {
            // If the space is empty, break from the process.
            if (board[row][i] == '-') {
                break;
            }

            // If space contains disc, move is valid.
            else if (board[row][i] == disc) {
                return true;
            }
        }
    }

    // Checks if adjacent space is occupied by opponent.
    if (board[row + 1][col] == opponentDisc) {
        // Iterates through the down spaces.
        for (int i = row + 2; i <= size; i++) {
            // If the space is empty, break from the process.
            if (board[i][col] == '-') {
                break;
            }

            // If space contains disc, move is valid.
            else if (board[i][col] == disc) {
                return true;
            }
        }
    }

    // Checks if adjacent space is occupied by opponent.
    if (board[row][col + 1] == opponentDisc) {
        // Iterates through the right spaces.
        for (int i = col + 2; i < size; i++) {
            // If the space is empty, break from the process.
            if (board[row][i] == '-') {
                break;
            }

            // If space contains disc, move is valid.
            else if (board[row][i] == disc) {
                return true;
            }
        }
    }

    // Checks if adjacent space is occupied by opponent.
    if (board[row - 1][col] == opponentDisc) {
        // Iterates through the up spaces.
        for (int i = row - 2; i >= 0; i--) {
            // If the space is empty, break from the process.
            if (board[i][col] == '-') {
                break;
            }

            // If space contains disc, move is valid.
            else if (board[i][col] == disc) {
                return true;
            }
        }
    }

    // Checks if adjacent space is occupied by opponent.
    if (board[row - 1][col + 1] == opponentDisc) {
        // Iterates through the up-right spaces.
        for (int i = row - 2, j = col - 2; i >= 0 && j >= 0; i--, j--) {
            // If the space is empty, break from the process.
            if (board[i][j] == '-') {
                break;
            }

            // If space contains disc, move is valid.
            else if (board[i][j] == disc) {
                return true;
            }
        }
    }

    // Checks if adjacent space is occupied by opponent.
    if (board[row + 1][col - 1] == opponentDisc) {
        // Iterates through the down-left spaces.
        for (int i = row + 2, j = col - 2; i <= size && j >= 0; i++, j--) {
            // If the space is empty, break from the process.
            if (board[i][j] == '-') {
                break;
            }

            // If space contains disc, move is valid.
            else if (board[i][j] == disc) {
                return true;
            }
        }
    }

    // Checks if adjacent space is occupied by opponent.
    if (board[row - 1][col + 1] == opponentDisc) {
        // Iterates through the up-right spaces.
        for (int i = row - 2, j = col + 2; i >= 0 && j <= size; i--, j++) {
            // If the space is empty, break from the process.
            if (board[i][j] == '-') {
                break;
            }

            // If space contains disc, move is valid.
            else if (board[i][j] == disc) {
                return true;
            }
        }
    }

    // Checks if adjacent space is occupied by opponent.
    if (board[row + 1][col + 1] == opponentDisc) {
        // Iterates through the down-right spaces.
        for (int i = row + 2, j = col + 2; i <= size && j <= size; i++, j++) {
            // If the space is empty, break from the process.
            if (board[i][j] == '-') {
                break;
            }

            // If space contains disc, move is valid.
            else if (board[i][j] == disc) {
                return true;
            }
        }
    }
    // Otherwise, return false.
    return false;
}

// Places the disc at location row,col and flips the opponent discs as needed.
void placeDiscAt(int size, char board[][size], int row, int col, char disc) {
    // Represents the opponentDisc disc color regarding the current player.
    char opponentDisc = getOpponentDisc(disc);

    // If move is not valid, return false.
    if (!isValidMove(size, board, row, col, disc)) {
        return;
    }

    // If move is valid, run through board game process.
    if (isValidMove(size, board, row, col, disc)) {
        // Add the disc to the designated location.
        board[row][col] = disc;

        // Checks if adjacent space is occupied by opponent.
        if (board[row][col - 1] == opponentDisc) {
            // Iterates through the left spaces.
            for (int i = col - 2; i >= 0; i--) {
                // When an empty space is encountered, break from process.
                if (board[row][i] == '-') {
                    break;
                }

                // Add current player's disc on board when appropriate.
                else if (board[row][i] == disc) {
                    for (int j = col - 1; j >= i; j--) {
                        board[row][j] = disc;
                    }
                }
            }
        }

        // Reassign right spaces to current player when appropriate.
        if (board[row + 1][col] == opponentDisc) {
            // Iterates through the down spaces.
            for (int i = row + 2; i <= size; i++) {
                // When an empty space is encountered, break from process.
                if (board[i][col] == '-') {
                    break;
                }

                // Add current player's disc on board when appropriate.
                else if (board[i][col] == disc) {
                    for (int j = row + 1; j <= i; j++) {
                        board[j][col] = disc;
                    }
                }
            }
        }

        // Reassign down spaces to current player when appropriate.
        if (board[row][col + 1] == opponentDisc) {
            // Iterates through the right spaces.
            for (int i = col + 2; i <= size; i++) {
                // When an empty space is encountered, break from process.
                if (board[row][i] == '-') {
                    break;
                }

                // Add current player's disc on board when appropriate.
                else if (board[row][i] == disc) {
                    for (int j = col + 1; j <= i; j++) {
                        board[row][j] = disc;
                    }
                }
            }
        }

        // Reassign left spaces to current player when appropriate.
        if (board[row - 1][col] == opponentDisc) {
            // Iterates through the up spaces.
            for (int i = row - 2; i >= 0; i--) {
                // When an empty space is encountered, break from process.
                if (board[i][col] == '-') {
                    break;
                }

                // Add current player's disc on board when appropriate.
                else if (board[i][col] == disc) {
                    for (int j = row - 1; j >= i; j--) {
                        board[j][col] = disc;
                    }
                }
            }
        }

        // Reassign up-left spaces to current player when appropriate.
        if (board[row - 1][col + 1] == opponentDisc) {
            // Iterates through the up-right spaces.
            for (int i = row - 2, j = col - 2; i >= 0 && j >= 0; i--, j--) {
                // When an empty space is encountered, break from process.
                if (board[i][j] == '-') {
                    break;
                }

                // Add current player's disc on board when appropriate.
                else if (board[i][j] == disc) {
                    for (int k = row - 1, l = col - 1; k >= i && l >= j; k--, l--) {
                        board[k][l] = disc;
                    }
                }
            }
        }

        // Reassign up-right spaces to current player when appropriate.
        if (board[row + 1][col - 1] == opponentDisc) {
            // Iterates through the down-left spaces.
            for (int i = row + 2, j = col - 2; i <= size && j >= 0; i++, j--) {
                // When an empty space is encountered, break from process.
                if (board[i][j] == '-') {
                    break;
                }

                // Add current player's disc on board when appropriate.
                else if (board[i][j] == disc) {
                    for (int k = row + 1, l = col - 1; k <= i && l >= j; k++, l--) {
                        board[k][l] = disc;
                    }
                }
            }
        }

        // Reassign down-left spaces to current player when appropriate.
        if (board[row - 1][col + 1] == opponentDisc) {
            // Iterates through the up-left spaces.
            for (int i = row - 2, j = col + 2; i >= 0 && j <= size; i--, j++) {
                // When an empty space is encountered, break from process.
                if (board[i][j] == '-') {
                    break;
                }

                // Add current player's disc on board when appropriate.
                else if (board[i][j] == disc) {
                    for (int k = row - 1, l = col + 1; k >= i && l <= j; k--, l++) {
                        board[k][l] = disc;
                    }
                }
            }
        }

        // Reassign down-right spaces to current player when appropriate.
        if (board[row + 1][col - 1] == opponentDisc) {
            // Iterates through the down-right spaces.
            for (int i = row + 2, j = col + 2; i <= size && j <= size; i++, j++) {
                // When an empty space is encountered, break from process.
                if (board[i][j] == '-') {
                    break;
                }

                // Add current player's disc on board when appropriate.
                else if (board[i][j] == disc) {
                    for (int k = row + 1, l = col + 1; k >= i && l >= j; k++, l++) {
                        board[k][l] = disc;
                    }
                }
            }
        }
    }
}

// Returns true if a valid move for disc is available; false otherwise.
bool isValidMoveAvailable(int size, char board[][size], char disc) {
    // Iterate through the rows of the board.
    for (int i = 0; i < size; i++) {
        // Iterate through the columns of the board.
        for (int j = 0; j < size; j++) {
            // Checks if space is currently empty.
            if (board[i][j] == '-') {
                // If the move is valid, return true.
                if (isValidMove(size, board, i, j, disc) == true) {
                    return true;
                }
            }
        }
    }
    // If a move is not valid, return false.
    return false;
}

// Returns true if the board is fully occupied with discs; false otherwise.
bool isBoardFull(int size, char board[][size]) {
    // Iterate through the rows of the board.
    for (int i = 0; i < size; i++) {
        // Iterate through the columns of the board.
        for (int j = 0; j < size; j++) {
            // If the board has empty spaces, return false.
            if (board[i][j] == '-') {
                return false;;
            }
        }
    }
    // If the board is full, return true.
    return true;
}

// Returns true if either the board is full or a valid move is not available for either disc; false otherwise.
bool isGameOver(int size, char board[][size]) {
    // If board is full, the game is over.
    if (isBoardFull(size, board)) {
        return true;
    }

    // If no valid moves available, the game is over.
    else if (!isValidMoveAvailable(size, board, 'W') && !isValidMoveAvailable(size, board, 'B')) {
        return true;
    }

    // Otherwise, the game remains active.
    return false;
}


// If there is a winner, it returns the disc (BLACK or WHITE) associated with the winner.
// In case of a tie, it returns TIE. When called before the game is over, it returns 0.
char checkWinner(int size, char board[][size]) {
    // Counts the amount of points allocated to each player.
    int whitePoints = 0;
    int blackPoints = 0;

    // If the game is not over, return 0.
    if (!isGameOver(size, board)) {
        return 0;
    }

    // Iterate through the rows of the board.
    for (int i = 0; i < size; i++) {
        // Iterate through the columns of the board.
        for (int j = 0; j < size; j++) {
            // If the space contains a white disc, add one point.
            if (board[i][j] == 'W') {
                whitePoints++;
            }

            // If the space contains a black disc, add one point.
            else if (board[i][j] == 'B') {
                blackPoints++;
            }
        }
    }

    // If player "White" has more points than player "Black", return "White" as winner.
    if (whitePoints > blackPoints) {
        return 'W';
    }

    // If player "Black" has more points than player "White", return "Black" as winner.
    else if (whitePoints < blackPoints) {
        return 'B';
    }

    // Otherwise, declare a tie.
    return 'T';
}
