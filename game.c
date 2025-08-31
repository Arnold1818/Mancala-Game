#include <stdio.h>
#include <stdlib.h>

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
    printf(" | CS | C7 | C5 | C4 | C3 | C2 | C1 |\n");
    printf("--------------------------------------\n");
    printf(" | ");
    printf("%d  | ", board[COMP_STORE]);
    for(int i = COMP_PITS - 1; i >= 0; i--) {
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

int userMove(int board[]) {
    int pit;
    // Ask for user input
    while(1) {
        printf("Your move! Choose a pit(1-6): ");
        scanf("%d", &pit);

        if(pit <= 0 || pit > 6) {
            printf("Invalid pit, Choose between 1 and 6.\n");
            continue;
        }
        if(board[pit-1] == 0) {
            printf("That pit is empty! Choose another.\n");
            continue;
        }
        break;
    }

    // Distribute stones
    int stones = board[pit - 1];
    board[pit - 1] = 0;
    int position = pit - 1;

    while(stones > 0) {
        position = (position + 1) % 14; // move to next slot
        if(position == 13) continue;    // skit computer's store
        board[position]++;
        stones--;
    }

    // Check for extra turn
    if(position == 6) {
        // printf("Last stone in your store! You get another turn.\n");
        return 1;   // return 1 means "extra turn"
    }

    // Check for capture
    if(position >= 0 && position <= 5 && board[position] == 1) {
        int opposite = 12 - position; // to get the opposite pit
        int captured = board[opposite];
        if(captured > 0) {
            board[6] += captured + 1;   // captured + user's last stone
            board[position] = 0;
            board[opposite] = 0;
            printf("Captured! You took %d stones from pit %d.\n", captured, opposite);
        }
    }

    return 0; // no extra turn
}

int compMove(int board[]) {
    int pit = -1;

    // pick first non-empty pit
    for(int i = 7; i <= 12; i++) {
        if(board[i] > 0) {
            pit = i;
            break;
        }
    }

    if(pit == -1) {
        printf("Computer has no moves!\n");
        return 0;
    }

    int stones = board[pit];
    board[pit] = 0;
    int position = pit;

    while(stones > 0) {
        position = (position + 1) % 14;     // move to next slot
        if(position == 6) continue;     // skip user's store
        board[position]++;
        stones--;
    }

    // extra turn if last stone in computer's store
    if(position == 13) {
        printf("Computer gets another turn!\n");
        return 1;
    }

    // check for capture
    if(position >= 7 && position <= 12 && board[position] == 1) {
        int opposite = 12 - position;
        int captured = board[opposite];
        if(captured > 0) {
            board[13] += captured + 1;  // captured + computer's last stone
            board[position] = 0;
            board[opposite] = 0;
            printf("Computer captured %d stones from pit %d!\n", captured, opposite);
        }
    }

    return 0;
}

int isGameOver(int board[]) {
    int userEmpty = 1, compEmpty = 1;

    // check user side (0–5)
    for (int i = 0; i < 6; i++) {
        if (board[i] != 0) {
            userEmpty = 0;
            break;
        }
    }

    // check computer side (7–12)
    for (int i = 7; i < 13; i++) {
        if (board[i] != 0) {
            compEmpty = 0;
            break;
        }
    }

    return (userEmpty || compEmpty);
}


int main() {
    int board[TOTAL];
    initBoard(board);
    // printArray(board);
    // displayBoard(board);

    while(1) {
        int again = userMove(board);
        system("cls");
        displayBoard(board);
        if(!again) {
            break;   // stop after one move testing
        } else {
            printf("Last stone in your store! You get another turn.\n");
        }
    }
    return 0;
}