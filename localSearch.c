#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 20 // Change N to the desired board size

// Initialize queen randomly with one queen per column
void initializeBoard(int board[N]) {
    int i;
    printf("Initial board: [");
    for (i = 0; i < N; i++) {
        board[i] = rand() % N;
        if(i == N - 1){
            printf("%d", board[i]);
            break;
        }
        printf("%d,", board[i]);
    }
    printf("]\n");
}

// Function to calculate the number of conflicting queens: calculates only row and diagonal conflicts
int calculateConflicts(int board[N]) {
    int conflicts = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (board[i] == board[j] || abs(board[i] - board[j]) == j - i) {
                conflicts++;
            }
        }
    }
    return conflicts;
}

int compareBoards(int board1[N], int board2[N]) {
    for (int i = 0; i < N; i++) {
        if (board1[i] != board2[i]) {
            return 0; // Boards are not equal
        }
    }
    return 1; // Boards are equal
}

void copyBoard(int source[N], int destination[N]) {
    for (int i = 0; i < N; i++) {
        destination[i] = source[i];
    }
}

// Function to move two queens to reduce the number of conflict
void move2Queens(int board[N], int queen1, int queen2, int *count) {

    int bestConflictValue = calculateConflicts(board);
    int bestQueen1 = board[queen1];
    int bestQueen2 = board[queen2];

    int previousBoard[N];
    int prevConflicts = bestConflictValue;

    if((*count) == 10000){
        bestQueen1 = rand() % N;
        bestQueen2 = rand() % N;
        (*count) = 0;
    }else{
        for(int i = 0; i < N; i++){
            board[queen1] = i;
            for(int j = 0; j < N; j++){
                board[queen2] = j;
                int newConflictValue = calculateConflicts(board);
                if(newConflictValue < bestConflictValue){
                    bestConflictValue   = newConflictValue;
                    bestQueen1 = i;
                    bestQueen2 = j;
                }
            }
        }
    }


    board[queen1] = bestQueen1;
    board[queen2] = bestQueen2;

    if (bestConflictValue < prevConflicts) {
        (*count) = 0; // Reset the count
    } else {
        (*count)++; // Increment count when no improvement
    }
}

void localSearch(int board[N]) {

    initializeBoard(board);

    int count = 0;

    while(calculateConflicts(board) != 0){

        //randomly choose 2 queens
        int queen1 = rand() % N;
        int queen2;
        do {
            queen2 = rand() % N;
        } while (queen2 == queen1);

        move2Queens(board, queen1, queen2, &count);
    }

    printf("Final board: [");
    for (int i = 0; i < N; i++) {
        if(i == N - 1){
            printf("%d", board[i]);
            break;
        }
        printf("%d,", board[i]);
    }
    printf("]\n"); 

}



int main() {
   int board[N];
   srand(time(NULL));
   localSearch(board);
}