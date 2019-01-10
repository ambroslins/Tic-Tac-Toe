#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

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

bool isLegalMove(const char *board, int move) {
    return board[move - 1] == ' ';
}

bool makeMove(char *board, int move, bool turn) {
    if(!isLegalMove(board, move)) return false;
    board[move -1] = (char) (turn ? 'X' : 'O');
    return true;
}

int getResult(const char *board) {
    //check diagonal
    char c = board[4];

    if(c != ' ' && ((c == board[0] && c == board[8]) || (c == board[2] && c == board[6]))) {
        return c == 'X' ? 1 : -1;
    }

    for (int i = 0; i < 3; ++i) {
        //check column
        c = board[i];
        if(c != ' ' && c == board[i+3] && c == board [i+6]) {
            return c == 'X' ? 1 : -1;
        }

        //check rows
        c = board[3*i];
        if(c != ' ' && c == board[3*i+1] && c == board[3*i+2]) {
            return c == 'X' ? 1 : -1;
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

int minimax(const char *board, bool turn) {
    if(isFinished(board)) return getResult(board);
    char newBoard[10];
    int score = turn ? -1 : 1;
    int nextScore;

    for (int i = 1; i < 10; ++i) {
        strcpy(newBoard, board);
        if(makeMove(newBoard, i, turn)) {
            nextScore = minimax(newBoard, !turn);
            score = turn ? max(nextScore, score) : min(nextScore, score);
        }
    }

    return score;
}

int aiMove(const char *board, bool turn) {
    char newBoard[10];
    int moveScore[9];

    for (int i = 0; i < 9; ++i) {
        strcpy(newBoard, board);
        if(makeMove(newBoard, i+1, turn)) {
            moveScore[i] = minimax(newBoard, !turn);
        } else {
            moveScore[i] = -2;
        }
        if(moveScore[i] == (turn ? 1 : -1)) return i+1; // take first winning move
    }

    for (int j = 0; j < 9; ++j) {
        if(moveScore[j] == 0) return j+1; // take first draw move
    }

    for (int k = 0; k < 9; ++k) {
        if(moveScore[k] == (turn ? -1 : 1)) return k+1; // take first losing move
    }

    fprintf(stderr, "can't find a move for %c", turn ? 'X' : 'O');
    drawBoard(board);
    exit(-1);
}

int main(int argc, char *argv[]) {
    char board[10];
    char input[100];
    bool turn; // true = 'X', false = 'O'
    int move, result; // 0 = draw, 1 = 'X' wins, -1 = 'O' wins
    bool ai = argc > 1 && strcmp(argv[1], "ai") == 0;



    puts("Tic Tac Toe by Ambros Lins");
    drawBoard("123456789");
    puts("Game starts!");

    while(true) {

        initBoard(board, &turn, &result);

        while(!isFinished(board) && result == 0) {

            if(ai && !turn) {
                makeMove(board, aiMove(board, turn), turn);
            } else{
                drawBoard(board);
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

            }


            turn = !turn;

            result = getResult(board);

        }

        drawBoard(board);
        printf("\n");

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