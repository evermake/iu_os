#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME "/tmp/ex1"
#define MAX_BUF 1024
#define WAIT_TIME 1

int main(int argc, char *argv[]) {
    if (argc > 1) {
        printf("Subscriber %s is here...\n", argv[1]);
    }

    fflush(stdout);

    int fd;
    char buf[MAX_BUF] = "";

    while (1) {
        fd = open(FIFO_NAME, O_RDONLY);

        if (fd == -1) {
            printf("Error opening FIFO %s\n", FIFO_NAME);
            return 1;
        }

        if (read(fd, buf, MAX_BUF) == -1) {
            printf("Error reading from FIFO %s\n", FIFO_NAME);
            return 2;
        }

        printf("%s", buf);

        close(fd);
    }

    return 0;
}
