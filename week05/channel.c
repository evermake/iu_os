#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUF_SIZE 1024

int main() {
    int pipe_fds[2];
    char buf[BUF_SIZE + 1] = {0};

    if (pipe(pipe_fds) == -1) {
        printf("Error opening pipe\n");
        exit(EXIT_FAILURE);
    }

    // Publisher child
    switch (fork()) {
        case -1:
            printf("Error forking publisher child\n");
            exit(EXIT_FAILURE);

        case 0:
            if (close(pipe_fds[0]) == -1) {
                printf("Error closing reading end of the pipe (by publisher)\n");
                exit(EXIT_FAILURE);
            }

            // Read messages from stdin and publish to the pipe
            while (fgets(buf, BUF_SIZE, stdin) != NULL) {
                size_t len = strlen(buf);
                if (write(pipe_fds[1], buf, len) != len) {
                    printf("Error writing to the pipe (by publisher)\n");
                    exit(EXIT_FAILURE);
                }
            }

            if (close(pipe_fds[1]) == -1) {
                printf("Error closing writing end of the pipe (by publisher)\n");
                exit(EXIT_FAILURE);
            }

            exit(EXIT_SUCCESS);

        default:
            break;
    }

    // Subscriber child
    switch (fork()) {
        case -1:
            printf("Error forking subscriber child\n");
            exit(EXIT_FAILURE);

        case 0:
            if (close(pipe_fds[1]) == -1) {
                printf("Error closing writing end of the pipe (by subscriber)\n");
                exit(EXIT_FAILURE);
            }

            // Read messages from the pipe and print to stdout
            while (1) {
                ssize_t bytes_read = read(pipe_fds[0], buf, BUF_SIZE);
                if (bytes_read == -1) {
                    printf("Error reading from the pipe (by subscriber)\n");
                    exit(EXIT_FAILURE);
                } else if (bytes_read == 0) {
                    break;
                } else {
                    buf[bytes_read] = '\0';
                }
                printf("%s", buf);
            }

            if (close(pipe_fds[0]) == -1) {
                printf("Error closing reading end of the pipe (by subscriber)\n");
                exit(EXIT_FAILURE);
            }

            exit(EXIT_SUCCESS);

        default:
            break;
    }

    // Close unused pipe ends
    if (close(pipe_fds[0]) == -1) {
        printf("Error closing reading end of the pipe (by parent)\n");
        exit(EXIT_FAILURE);
    }
    if (close(pipe_fds[1]) == -1) {
        printf("Error closing writing end of the pipe (by parent)\n");
        exit(EXIT_FAILURE);
    }

    // Wait for children to finish
    int status;
    while (wait(&status) > 0) {
        if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS) {
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}
