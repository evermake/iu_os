#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define FIFO_NAME "/tmp/ex1"
#define MAX_BUF 1024
#define SLEEP_TIME 1

int main(int argc, char *argv[]) {
    int n_copies = 1;
    if (argc > 1) {
        n_copies = atoi(argv[1]);
        if (n_copies < 1) {
            printf("Usage: %s [n_copies]\n", argv[0]);
            return 1;
        }
    }

    printf("Publisher is here...\n");

    int fd;
    char buf[MAX_BUF] = "";

    if (mkfifo(FIFO_NAME, 0666) == -1) {
        // Ignore case if FIFO already exists
        if (errno != EEXIST) {
            printf("Error creating FIFO %s\n", FIFO_NAME);
            return 1;
        }
    }

    while (1) {
        fgets(buf, MAX_BUF, stdin);
        fd = open(FIFO_NAME, O_WRONLY);
        for (int i = 0; i < n_copies; i++) {
            if (write(fd, buf, MAX_BUF) == -1) {
                printf("Error writing to FIFO %s\n", FIFO_NAME);
                return 3;
            }
        }
        close(fd);
        sleep(SLEEP_TIME);
    }

    return 0;
}
