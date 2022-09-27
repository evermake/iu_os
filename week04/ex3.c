#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define USAGE "Usage: ex3 <n>\n"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf(USAGE);
        exit(1);
    }
    int n = atoi(argv[1]);

    for (int i = 0; i < n; i++) {
        fork();
        sleep(5);
    }
}
