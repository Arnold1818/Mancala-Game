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

void displayBoard(int board[]) {
    printf("\n");
    printf("              COMPUTER                \n");
    printf("--------------------------------------\n");
    printf(" | C6 | C5 | C4 | C3 | C2 | C1 | CS |\n");
    printf("--------------------------------------\n");
    printf(" | ");
    for(int i = 0; i < COMP_PITS + 1; i++) {
        printf("%d  | ", board[i + 7]);
    }
    printf("\n");
    printf("--------------------------------------\n\n");
    printf("--------------------------------------\n");
    printf(" | U1 | U2 | U3 | U4 | U5 | U6 | US |\n");
    printf("--------------------------------------\n");
    printf(" | ");
    for(int i = 0; i < COMP_PITS + 1; i++) {
        printf("%d  | ", board[i]);
    }
    printf("\n--------------------------------------\n");
    printf("                USER                \n");

}

int main() {
    int board[TOTAL];
    initBoard(board);
    // printArray(board);
    displayBoard(board);
    return 0;
}