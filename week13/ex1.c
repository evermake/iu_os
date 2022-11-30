#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_PATH "input.txt"
#define DEFAULT_RESOURCES_NUM 3
#define DEFAULT_PROCESSES_NUM 5

int main(int argc, char *argv[]) {
    int resNum, procNum;
    if (argc == 1) {
        resNum = DEFAULT_RESOURCES_NUM;
        procNum = DEFAULT_PROCESSES_NUM;
    } else if (argc == 3) {
        resNum = atoi(argv[1]);
        procNum = atoi(argv[2]);
        if (resNum <= 0 || procNum <= 0) {
            perror("must be positive integers");
            return 1;
        }
    } else {
        printf("Usage: %s [resNum] [procNum]\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *input = fopen(INPUT_PATH, "r");
    if (input == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    int E[resNum], A[resNum];
    int C[procNum][resNum], R[procNum][resNum];

    // parse input file
    for (int i = 0; i < resNum; i++) {
        fscanf(input, "%d", &E[i]);
    }
    for (int i = 0; i < resNum; i++) {
        fscanf(input, "%d", &A[i]);
    }
    for (int i = 0; i < procNum; i++) {
        for (int j = 0; j < resNum; j++) {
            fscanf(input, "%d", &C[i][j]);
        }
    }
    for (int i = 0; i < procNum; i++) {
        for (int j = 0; j < resNum; j++) {
            fscanf(input, "%d", &R[i][j]);
        }
    }

    // validate input
    for (int i = 0; i < resNum; i++) {
        if (E[i] < 0 || A[i] < 0) {
            perror("E and A must be positive integers");
            return 1;
        }
    }
    for (int i = 0; i < procNum; i++) {
        for (int j = 0; j < resNum; j++) {
            if (C[i][j] < 0 || R[i][j] < 0) {
                perror("C and R must be positive integers");
                return 1;
            }
        }
    }

    // check input is correct
    int sum = 0;
    for (int i = 0; i < resNum; i++) {
        sum += A[i];
    }
    if (sum > resNum) {
        perror("A must be less than or equal to E");
        return 1;
    }

    // detect deadlocks
    int deadlocks = 0;
    int finish[procNum];
    for (int i = 0; i < procNum; i++) {
        finish[i] = 0;
    }
    int work[resNum];
    for (int i = 0; i < resNum; i++) {
        work[i] = A[i];
    }
    int found = 1;
    while (found) {
        found = 0;
        for (int i = 0; i < procNum; i++) {
            if (finish[i] == 0) {
                int canFinish = 1;
                for (int j = 0; j < resNum; j++) {
                    if (R[i][j] > work[j]) {
                        canFinish = 0;
                        break;
                    }
                }
                if (canFinish) {
                    for (int j = 0; j < resNum; j++) {
                        work[j] += C[i][j];
                    }
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
    }
    for (int i = 0; i < procNum; i++) {
        if (finish[i] == 0) {
            deadlocks++;
        }
    }
    
    if (deadlocks == 0) {
        printf("No deadlocks detected!🙂\n");
    } else {
        printf("Detected: %d deadlocks 😢\n", deadlocks);
    }

    fclose(input);
    return EXIT_SUCCESS;
}
