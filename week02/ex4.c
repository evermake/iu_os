#include <stdio.h>
#include <string.h>
#define STRING_SIZE 256

char lower(char c) {
    if ('A' <= c && c <= 'Z') return c - 'A' + 'a';
    return c;
}

int count(char s[STRING_SIZE], char c) {
    c = lower(c);
    int occurrences = 0;
    for (int i = 0; i < STRING_SIZE; i++) {
        char sc = s[i];
        if (sc == '\0') break;
        sc = lower(sc);
        if (sc == c) occurrences++;
    }
    return occurrences;
}

void countAll(char s[STRING_SIZE]) {
    int occurrences = 0;
    for (int i = 0; i < STRING_SIZE; i++) {
        char sc = s[i];
        if (sc == '\0') break;
        sc = lower(sc);
        occurrences = count(s, sc);
        printf("%c:%d", sc, occurrences);

        int isLast = i + 1 >= STRING_SIZE || s[i+1] == '\0';
        if (!isLast) printf(", ");
    }
    printf("\n");
}

int main() {
    char s[STRING_SIZE] = {};
    fgets(s, STRING_SIZE, stdin);

    // Remove trailing '\n' symbol
    size_t len = strlen(s);
    if (len > 0 && s[len-1] == '\n') s[len-1] = '\0';

    countAll(s);
}
