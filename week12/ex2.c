#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <errno.h>

#define DEV_PATH "/dev/input/by-path/platform-i8042-serio-0-event-kbd"

int main() {
    int fd;
    struct input_event ev;
    ssize_t n;

    FILE *fout = fopen("ex2.txt", "w");
    if (fout == NULL) {
        perror("error opening file");
        exit(EXIT_FAILURE);
    }

    fd = open(DEV_PATH, O_RDONLY);
    if (fd == -1) {
        perror("error opening device");
        exit(EXIT_FAILURE);
    }

    while (1) {
        n = read(fd, &ev, sizeof ev);
        if (n == (ssize_t)-1) {
            if (errno == EINTR)
                continue;
            else
                break;
        } else if (n != sizeof ev) {
            errno = EIO;
            break;
        }

        if (ev.type == EV_KEY) {
            // Print only press & release events
            if (ev.value == 1) {
                printf("PRESSED 0x%04x (%d)\n", ev.code, ev.code);
                fprintf(fout, "PRESSED 0x%04x (%d)\n", ev.code, ev.code);
            }

            else if (ev.value == 0) {
                printf("RELEASED 0x%04x (%d)\n", ev.code, ev.code);
                fprintf(fout, "RELEASED 0x%04x (%d)\n", ev.code, ev.code);
            }
            fflush(fout);
        }
    }

    fclose(fout);
    close(fd);
    fflush(stdout);
    exit(EXIT_FAILURE);
}
