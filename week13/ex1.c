#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_PATH "input.txt"
#define MAX_LINE_SIZE 255


void malformed() {
    perror("malformed input\n");
    exit(EXIT_FAILURE);
}

int readFirstLineWithNumbers(char *line, FILE *input) {
    while (fgets(line, MAX_LINE_SIZE, input) != NULL) {
        if (line[0] == '#') {
            continue;
        }
        bool wasDigit = false;
        int count = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            if ('0' <= line[i] && line[i] <= '9') {
                if (!wasDigit) {
                    count++;
                    wasDigit = true;
                }
            } else {
                wasDigit = false;
            }
        }
        if (count > 0) {
            return count;
        }
    }
    return 0;
}

int* readNonnegativeNumbers(FILE* f, int* size) {
    char line[MAX_LINE_SIZE];
    int numsCount = readFirstLineWithNumbers(line, f);

    if (numsCount == 0) {
        *size = 0;
        return NULL;
    }

    int *nums = (int *) malloc(numsCount * sizeof(int));
    if (nums == NULL) {
        perror("malloc failed\n");
        exit(EXIT_FAILURE);
    }
    // read and parse numbers from line
    int i = 0;
    char *token = strtok(line, " ");
    while (token != NULL && i < numsCount) {
        int num = atoi(token);
        if (num < 0) {
            perror("numbers must be non-negative\n");
            malformed();
        }
        nums[i] = num;
        i++;
        token = strtok(NULL, " \t");
    }
    *size = i;
    return nums;
}

int main(int argc, char *argv[]) {
    char line[MAX_LINE_SIZE];

    FILE *input = fopen(INPUT_PATH, "r");
    if (input == NULL) {
        perror("error opening \"input.txt\"\n");
        exit(EXIT_FAILURE);
    }

    int resExistCount;
    int* E = readNonnegativeNumbers(input, &resExistCount);
    if (E == NULL) malformed();

    int resAvailableCount;
    int* A = readNonnegativeNumbers(input, &resAvailableCount);
    if (A == NULL || resExistCount != resAvailableCount) {
        perror("number of existing and available resources must be equal\n");
        malformed();
    }
    int resNum = resExistCount;

    int cap = 10;
    int** rows = malloc(cap * sizeof(int*));
    int rowsRead = 0;
    while (true) {
        int rowSize;
        int* row = readNonnegativeNumbers(input, &rowSize);
        if (rowSize == 0) {
            free(row);
            break;
        }
        if (rowSize != resNum) {
            perror("number of resources in each row must be equal to the number of resources\n");
            malformed();
        }
        if (rowsRead == cap) {
            cap *= 2;
            rows = realloc(rows, cap * sizeof(int*));
        }
        rows[rowsRead] = row;
        rowsRead++;
    }

    if (rowsRead == 0) {
        perror("no C and R matrices\n");
        malformed();
    }

    if (rowsRead % 2 != 0) {
        perror("number of rows in C and R must be equal\n");
        malformed();
    }

    int procNum = rowsRead / 2;

    int** C = malloc(procNum * sizeof(int*));
    int** R = malloc(procNum * sizeof(int*));

    for (int i = 0; i < procNum; i++) {
        C[i] = rows[i];
        R[i] = rows[procNum + i];
    }

    // check available resources not bigger than existing
    for (int i = 0; i < resExistCount; i++) {
        if (A[i] > E[i]) {
            perror("available resources must not be more than existing\n");
            malformed();
        }
    }

    // validate C and R matrices
    int* totalResAlloc = malloc(resNum * sizeof(int));
    for (int i = 0; i < resNum; i++) {
        totalResAlloc[i] = 0;
    }
    for (int i = 0; i < procNum; i++) {
        for (int j = 0; j < resNum; j++) {
            int alloc = C[i][j];
            // int want = R[i][j];
            totalResAlloc[j] += alloc;
            // if (alloc > E[j]) {
            //     perror("processes cannot use more resources than exist\n");
            //     malformed();
            // }
        }
    }
    for (int i = 0; i < resNum; i++) {
        if (totalResAlloc[i] > E[i]) {
            perror("total resources allocated cannot be more than existing\n");
            malformed();
        } else if (totalResAlloc[i] + A[i] != E[i]) {
            perror("total resources allocated plus available must be equal to existing\n");
            malformed();
        }
    }
    free(totalResAlloc);

    // detect deadlocks
    bool* finished = malloc(procNum * sizeof(bool));
    for (int i = 0; i < procNum; i++) {
        finished[i] = false;
    }
    bool wasChange = true;
    while (wasChange) {
        wasChange = false;
        for (int i = 0; i < procNum; i++) {
            if (!finished[i]) {
                bool canFinish = 1;
                for (int j = 0; j < resNum; j++) {
                    if (R[i][j] > A[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                    for (int j = 0; j < resNum; j++) {
                        A[j] += C[i][j];
                    }
                    finished[i] = true;
                    wasChange = true;
                }
            }
        }
    }
    bool wasDeadlock = false;
    for (int i = 0; i < procNum; i++) {
        if (!finished[i]) {
            wasDeadlock = true;
            printf("P%d deadlocked\n", i+1);
        }
    }
    if (!wasDeadlock) {
        printf("No deadlocks🙂\n");
    }

    free(finished);
    free(E);
    free(A);
    free(C);
    free(R);
    for (int i = 0; i < rowsRead; i++) {
        free(rows[i]);
    }
    free(rows);

    fclose(input);
    return EXIT_SUCCESS;
}
