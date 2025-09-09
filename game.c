#include <stdio.h>
#include <stdlib.h>

#define USER_PITS 6
#define COMP_PITS 6
#define STONES 4

#define USER_STORE 6
#define COMP_STORE 13
#define TOTAL 14

#define MAX_DEPTH 5  // search depth

// Function Prototypes 
void initBoard(int board[]);
void printArray(int board[]);
void displayBoard(int board[]);
int userMove(int board[]);
int compMove(int board[]);
int evaluateBoard(int board[]);
int makeMove(int board[], int pit, int player);
int minimax(int board[], int depth, int alpha, int beta, int isMaximizing);
int isGameOver(int board[]);

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
    printf(" ------------------------------------\n");
    printf(" | CS | C6 | C5 | C4 | C3 | C2 | C1 |\n");
    printf(" ------------------------------------\n");
    printf(" | ");
    printf("%d  | ", board[COMP_STORE]);
    for(int i = COMP_PITS - 1; i >= 0; i--) {
        printf("%d  | ", board[i + 7]);
    }
    printf("\n");
    printf(" ------------------------------------ \n\n");
    printf("      ------------------------------------\n");
    printf("      | U1 | U2 | U3 | U4 | U5 | U6 | US |\n");
    printf("      ------------------------------------\n");
    printf("      | ");
    for(int i = 0; i < COMP_PITS + 1; i++) {
        printf("%d  | ", board[i]);
    }
    printf("\n      ------------------------------------ \n");
    printf("                      USER                \n");

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
            printf("Press Enter to continue...");
            getchar(); // consume leftover newline
            getchar(); // wait for Enter
        }
    }

    return 0; // no extra turn
}

// Simple Approach
// int compMove(int board[]) {
//     int pit = -1;

//     // pick first non-empty pit
//     for(int i = 7; i <= 12; i++) {
//         if(board[i] > 0) {
//             pit = i;
//             break;
//         }
//     }

//     if(pit == -1) {
//         printf("Computer has no moves!\n");
//         printf("Press Enter to continue...");
//         getchar(); // consume leftover newline
//         getchar(); // wait for Enter
//         return 0;
//     }

//     int stones = board[pit];
//     board[pit] = 0;
//     int position = pit;

//     while(stones > 0) {
//         position = (position + 1) % 14;     // move to next slot
//         if(position == 6) continue;     // skip user's store
//         board[position]++;
//         stones--;
//     }

//     // extra turn if last stone in computer's store
//     if(position == 13) {
//         printf("Computer gets another turn!\n");
//         printf("Press Enter to continue...");
//         getchar(); // consume leftover newline
//         getchar(); // wait for Enter
//         return 1;
//     }

//     // check for capture
//     if(position >= 7 && position <= 12 && board[position] == 1) {
//         int opposite = 12 - position;
//         int captured = board[opposite];
//         if(captured > 0) {
//             board[13] += captured + 1;  // captured + computer's last stone
//             board[position] = 0;
//             board[opposite] = 0;
//             printf("Computer captured %d stones from pit %d!\n", captured, opposite);
//             printf("Press Enter to continue...");
//             getchar(); // consume leftover newline
//             getchar(); // wait for Enter
//         }
//     }

//     return 0;
// }


int evaluateBoard(int board[]) {
    return board[COMP_STORE] - board[USER_STORE];
}

// Simulates a move for a player and updates board
// Returns 1 if extra turn granted, else 0
int makeMove(int board[], int pit, int player) {
    int start = (player == 0) ? 0 : 7; // 0=user, 1=comp
    int end   = (player == 0) ? 5 : 12;
    int store = (player == 0) ? USER_STORE : COMP_STORE;
    int oppStore = (player == 0) ? COMP_STORE : USER_STORE;

    int stones = board[pit];
    if(stones == 0) return -1; // invalid
    board[pit] = 0;

    int pos = pit;
    while(stones > 0) {
        pos = (pos + 1) % TOTAL;
        if(pos == oppStore) continue; // skip opponent store
        board[pos]++;
        stones--;
    }

    // extra turn
    if(pos == store) return 1;

    // capture
    if(pos >= start && pos <= end && board[pos] == 1) {
        int opposite = 12 - pos;
        int captured = board[opposite];
        if(captured > 0) {
            board[store] += captured + 1;
            board[pos] = 0;
            board[opposite] = 0;
        }
    }

    return 0;
}

int minimax(int board[], int depth, int alpha, int beta, int isMaximizing) {
    if(depth == 0 || isGameOver(board)) {
        return evaluateBoard(board);
    }

    if(isMaximizing) { // computer's turn
        int maxEval = -9999;
        for(int pit = 7; pit <= 12; pit++) {
            if(board[pit] == 0) continue;

            int temp[TOTAL];
            for(int i=0; i<TOTAL; i++) temp[i] = board[i];

            int extraTurn = makeMove(temp, pit, 1);
            int eval;
            if(extraTurn == 1)
                eval = minimax(temp, depth-1, alpha, beta, 1); // go again
            else
                eval = minimax(temp, depth-1, alpha, beta, 0);

            if(eval > maxEval) maxEval = eval;
            if(eval > alpha) alpha = eval;
            if(beta <= alpha) break; // prune
        }
        return maxEval;
    } else { // user's turn (minimizer)
        int minEval = 9999;
        for(int pit = 0; pit <= 5; pit++) {
            if(board[pit] == 0) continue;

            int temp[TOTAL];
            for(int i=0; i<TOTAL; i++) temp[i] = board[i];

            int extraTurn = makeMove(temp, pit, 0);
            int eval;
            if(extraTurn == 1)
                eval = minimax(temp, depth-1, alpha, beta, 0); // user again
            else
                eval = minimax(temp, depth-1, alpha, beta, 1);

            if(eval < minEval) minEval = eval;
            if(eval < beta) beta = eval;
            if(beta <= alpha) break; // prune
        }
        return minEval;
    }
}

int compMove(int board[]) {
    int bestPit = -1;
    int bestScore = -9999;

    for(int pit = 7; pit <= 12; pit++) {
        if(board[pit] == 0) continue;

        int temp[TOTAL];
        for(int i=0; i<TOTAL; i++) temp[i] = board[i];

        int extraTurn = makeMove(temp, pit, 1);
        int eval;
        if(extraTurn == 1)
            eval = minimax(temp, MAX_DEPTH, -9999, 9999, 1);
        else
            eval = minimax(temp, MAX_DEPTH, -9999, 9999, 0);

        if(eval > bestScore) {
            bestScore = eval;
            bestPit = pit;
        }
    }

    if(bestPit == -1) {
        printf("Computer has no moves!\n");
        return 0;
    }

    printf("Computer chooses pit C%d\n", 13 - bestPit);

    // play real move
    int extraTurn = makeMove(board, bestPit, 1);
    if(extraTurn) {
        printf("Computer gets another turn!\n");
        return 1;
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
    int choice;
    while(1) {
        system("cls"); 
        printf("====================================\n");
        printf("             GAME MENU\n");
        printf("====================================\n");
        printf("1. New Game\n");
        printf("2. Game Rules\n");
        printf("3. Exit\n");
        printf("====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if(choice == 1) {
            //    Start New Game 
            int board[TOTAL];
            initBoard(board);

            while(!isGameOver(board)) {
                int again;

                // User Move
                do {
                    again = userMove(board);
                    system("cls");
                    displayBoard(board);
                    if(again) {
                        printf("Last stone in your store! You get another turn.\n");
                    }
                } while(again && !isGameOver(board));

                // Computer Move
                do {
                    again = compMove(board);
                    system("cls");
                    displayBoard(board);
                    if(again) {
                        printf("Computer gets another turn!\n");
                    }
                } while(again && !isGameOver(board));
            }

            //    Game Ends... collect all stones 
            for(int i = 0; i < 6; i++) {
                board[6] += board[i];
                board[i] = 0;
            }
            for(int i = 7; i < 13; i++) {
                board[13] += board[i];
                board[i] = 0;
            }

            system("cls");
            displayBoard(board);

            printf("\nGame Over!\n");
            if(board[6] > board[13]) {
                printf("Congratulations! You win.\n\n");
            } else if(board[6] < board[13]) {
                printf("Better luck next time! Computer wins.\n\n");
            } else {
                printf("It's a tie!\n\n");
            }

            printf("Press Enter to return to menu...");
            getchar(); getchar(); // wait
        } 
        else if(choice == 2) {
            // Game Rules 
            system("cls");
            printf("=============== GAME RULES ===============\n");
            printf("1. The board has 6 pits for each player and 1 store.\n");
            printf("2. On your turn, pick stones from one of your pits.\n");
            printf("3. Stones are placed one-by-one into subsequent pits,\n");
            printf("   including your store, but skipping opponent's store.\n");
            printf("4. If your last stone lands in your store, you get another turn.\n");
            printf("5. If your last stone lands in an empty pit on your side,\n");
            printf("   you capture that stone + stones in the opposite pit.\n");
            printf("6. Game ends when one side's pits are all empty.\n");
            printf("7. Remaining stones go to the other player's store.\n");
            printf("8. Player with most stones in store wins!\n");
            printf("==========================================\n\n");

            printf("Press Enter to return to menu...");
            getchar(); getchar(); // wait
        } 
        else if(choice == 3) {
            printf("See You Again... Goodbye!\n");
            break;
        } 
        else {
            printf("Invalid choice! Try again.\n");
            getchar(); getchar();
        }
    }
    return 0;
}
