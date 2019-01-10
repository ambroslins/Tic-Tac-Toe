#include <stdio.h>
#include <string.h>

void drawBoard(const char *board) {
    if(board == NULL || strlen(board) < 9) return;
    printf(" %c | %c | %c \n", board[0], board[1], board[2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", board[3], board[4], board[5]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", board[6], board[7], board[8]);
}

int main() {
    drawBoard("123456789");
        
    return 0;
}