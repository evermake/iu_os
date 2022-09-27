/* Simplistic $hell */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <errno.h>

// Max length of a line
#define MAX_LINE 100

// Delimiters of arguments
#define DELIM " \t\r\n"

// Some colors
#define C_RED "\x1b[31m"
#define C_GREEN "\x1b[32m"
#define C_BLUE "\x1b[34m"
#define C_DEFAULT "\x1b[0m"

/**
 * Parse whitespace separated arguments from string.
 */
int parse_args(char* input, char* args[]) {
    char *token;
    int i = 0;

    token = strtok(input, DELIM);
    while (token != NULL) {
        args[i] = token;
        token = strtok(NULL, DELIM);
        i++;
    }
    args[i] = NULL;

    return i;
}

int main() {
    char input[MAX_LINE];
    char *args[MAX_LINE/2 + 1];
    int exit_status = 0;

    printf("  _   _            _  _ \n");
    printf(" | | | |__    ___ / |/ |\n");
    printf("/ __)| '_ \\  / _ \\| || |\n");
    printf("\\__ \\| | | ||  __/| || |\n");
    printf("(   /|_| |_| \\___||_||_|\n");
    printf(" |_|                    \n");
    printf("\n\n");

    while (true) {
        if (exit_status != 0) {
            printf("%s[%d]%s$%s ", C_RED, exit_status, C_BLUE, C_DEFAULT);
        } else {
            printf("%s$%s ", C_BLUE, C_DEFAULT);
        }
        fflush(stdout);

        fgets(input, MAX_LINE, stdin);
        int args_count = parse_args(input, args);

        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        bool in_background = false;
        if (strcmp(args[args_count - 1], "&") == 0) {
            in_background = true;
            args[--args_count] = NULL;
        }

        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            execvp(args[0], args);
            printf("Unknown command: %s%s%s\n", C_RED, args[0], C_DEFAULT);
            exit(0);
        }

        exit_status = 0;
        if (!in_background) {
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) {
                exit_status = WEXITSTATUS(status);
            }
        }
    }

    return 0;
}
