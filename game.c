#include <stdio.h>

#define USER_PITS 6
#define COMP_PITS 6
#define STONES 4

#define USER_STORE 6
#define COMP_STORE 13
#define TOTAL 14

void initBoard(int board[]) {
    // initialize user pits
    for(int i = 0; i < USER_PITS; i++) {
        board[i] = STONES;
    }
    board[USER_STORE] = 0;

    // initialize computer pits
    for(int i = 0; i < COMP_PITS; i++) {
        board[i + 7] = STONES;
    }
    board[COMP_STORE] = 0;
}

void printArray(int board[]) {
    printf("Board Array: \n");
    for(int i = 0; i < TOTAL; i++) {
        if(i == 7) {
            printf("\n");
        }
        printf("[%d] ", board[i]);
    }
}

int main() {
    int board[TOTAL];
    initBoard(board);
    printArray(board);
    return 0;
}