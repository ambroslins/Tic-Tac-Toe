#include <stdio.h>
#include <string.h>
#include <stdbool.h>

enum State{Blank, X, O};


void drawBoard(const char *board) {
    printf(" %c | %c | %c \n", board[0], board[1], board[2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", board[3], board[4], board[5]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", board[6], board[7], board[8]);
}


bool isFinished(const char *board) {
    return strchr(board, ' ') == NULL;
}

bool makeMove(char *board, int move, bool turn) {
    if(board[move - 1] != ' ') return false;
    board[move -1] = (char) (turn ? 'X' : 'O');
    return true;
}

int getResult(const char *board) {
    //check diagonal
    char c = board[4];

    if(c != ' ' && ((c == board[0] && c == board[8]) || (c == board[2] && c == board[6]))) {
        return c == 'X' ? 1 : 2;
    }

    for (int i = 0; i < 3; ++i) {
        //check column
        c = board[i];
        if(c != ' ' && c == board[i+3] && c == board [i+6]) {
            return c == 'X' ? 1 : 2;
        }

        //check rows
        c = board[3*i];
        if(c != ' ' && c == board[i+1] && c == board[i+2]) {
            return c == 'X' ? 1 : 2;
        }
    }


    return 0;
}

int main() {
    char board[] = "         ";
    bool turn = true; // true = 'X', false = 'O'
    int move;
    int result = 0; // 0 = draw, 1 = 'X' wins, 2 = 'O' wins

    drawBoard(board);
    while(!isFinished(board) && result == 0) {
        printf("%c moves: ", turn ? 'X' : 'O');
        if(scanf("%d", &move) != 1 || move < 1 || move > 9) {
            puts("Illegal input");
            continue;
        }

        if(!makeMove(board, move, turn)) {
            puts(("Illegal move"));
            continue;
        }

        turn = !turn;

        drawBoard(board);

        result = getResult(board);
    }

    if(result == 0) {
        puts("Draw");
    } else {
        printf("%c Wins!!!", result == 1 ? 'X' : 'O');
    }

    return 0;
}