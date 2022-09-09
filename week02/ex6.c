#include <stdio.h>
#include <stdlib.h>

void printPatternA(int n) {
    if (n <= 0) return;
    char* s0 = calloc(n, sizeof(char));
    char* s = s0;
    for (int i = 0; i < n; i++) {
        *(s++) = '*';
        printf("%s\n", s0);
    }
    free(s0);
}

void printPatternB(int n) {
    if (n <= 0) return;
    char* s0 = calloc(n/2+1, sizeof(char));
    char* s = s0;

    n = n / 2 + (n % 2);

    int i = 0;
    for (; i < n; i++) {
        *(s++) = '*';
        printf("%s\n", s0);
    }
    i--;
    for (; i >= 0; i--) {
        *(s--) = '\0';
        printf("%s\n", s0);
    }

    free(s0);
}

void printPatternC(int n) {
    if (n <= 0) return;
    char* s0 = calloc(n, sizeof(char));
    char* s = s0;
    for (int i = 0; i < n; i++)
        *(s++) = '*';
    for (int i = 0; i < n; i++)
        printf("%s\n", s0);
    free(s0);
}

int main() {
    printPatternA(7);
    printf("\n");
    printPatternB(7);
    printf("\n");
    printPatternC(7);
}
