#include <stdio.h>
#include <string.h>
#include <stdbool.h>

enum State{Blank, X, O};


void drawBoard(const char *board) {
    printf("\n");
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

void initBoard(char *board, bool *turn, int *result) {
    static int games = 0;
    strcpy(board, "         ");
    *turn = (bool) (++games & 1);
    *result = 0;
}

int main() {
    char board[10];
    char input[100];
    bool turn; // true = 'X', false = 'O'
    int move, result; // 0 = draw, 1 = 'X' wins, 2 = 'O' wins



    puts("Tic Tac Toe by Ambros Lins");
    drawBoard("123456789");
    puts("Press ENTER key to Continue");
    getchar();


    while(true) {

        initBoard(board, &turn, &result);

        drawBoard(board);
        while(!isFinished(board) && result == 0) {
            printf("%c moves: ", turn ? 'X' : 'O');
            fgets(input, sizeof(input), stdin);
            if(strcmp(input, "exit\n") == 0) return 0;
            if(sscanf(input, "%d", &move) != 1 || move < 1 || move > 9) {
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

        if (result == 0) {
            puts("Draw");
        } else {
            printf("%c Wins!!!\n\n", result == 1 ? 'X' : 'O');
        }

        puts("Would you like to play again? (y=yes/n=no)");
        fgets(input, sizeof(input), stdin);
        if(!(input[0] == 'y' || input[0] == 'Y')) break;


    }


    return 0;
}