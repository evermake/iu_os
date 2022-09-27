#include <stdio.h>
#include <time.h>
#include <unistd.h>

/*
 * Convert difference between clock ticks between current
 * ticks count and the start to time milliseconds and return it.
 */
long double get_ms_from_start_clocks(clock_t start) {
    clock_t d = clock() - start;
    return ((long double)d) / ((long double)(CLOCKS_PER_SEC)) * 1000;
}

int main() {
    pid_t my_pid, parent_pid;
    pid_t fork_1_pid = fork();
    const clock_t start1 = clock();

    if (fork_1_pid == 0) {
        // First child process
        my_pid = getpid();
        parent_pid = getppid();
        printf("PID = %d, Parent PID = %d\n", my_pid, parent_pid);
        printf("PID = %d, execution time = %Lfms\n", my_pid, get_ms_from_start_clocks(start1));
    } else {
        pid_t fork_2_pid = fork();
        const clock_t start2 = clock();

        if (fork_2_pid == 0) {
            // Second child
            my_pid = getpid();
            parent_pid = getppid();
            printf("PID = %d, Parent PID = %d\n", my_pid, parent_pid);
            printf("PID = %d, execution time = %Lfms\n", my_pid, get_ms_from_start_clocks(start2));
        } else {
            // Main process
            my_pid = getpid();
            parent_pid = getppid();
            printf("PID = %d, Parent PID = %d\n", my_pid, parent_pid);
            printf("PID = %d, execution time = %Lfms\n", my_pid, get_ms_from_start_clocks(start1));
        }
    }
}
