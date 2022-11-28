#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <errno.h>

#define DEV_PATH "/dev/input/by-path/platform-i8042-serio-0-event-kbd"

typedef struct {
    char* message;
    int* keys;
    int keys_len;
    char* help;
} Shortcut;

int main() {
    struct input_event ev;
    ssize_t n;

    int fd = open(DEV_PATH, O_RDONLY);
    if (fd == -1) {
        perror("error opening device");
        exit(EXIT_FAILURE);
    }

    FILE *fout = fopen("ex3.txt", "w");
    if (fout == NULL) {
        perror("error opening file");
        exit(EXIT_FAILURE);
    }

    Shortcut shortcuts[3] = {
        {"I passed the Exam!", (int[]){ KEY_P, KEY_E }, 2, "P + E"},
        {"Get some cappuccino!", (int[]){ KEY_C, KEY_A, KEY_P }, 3, "C + A + P"},
        {"amougus : )", (int[]){ KEY_F, KEY_J }, 2, "F + J"}
    };

    printf("Available shortcuts: (do not press Shift)\n");
    for (int i = 0; i < sizeof(shortcuts) / sizeof(shortcuts[0]); i++) {
        printf("\t%d. %s (%s)\n", i + 1, shortcuts[i].message, shortcuts[i].help);
    }

    int pressed_keys[256] = {0};
    int total_pressed_keys = 0;

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
            int pressed_or_hold = 0;
            if (ev.value == 0) {
                if (0 <= ev.code && ev.code < 256 && pressed_keys[ev.code] == 1) {
                    pressed_keys[ev.code] = 0;
                    total_pressed_keys--;
                }
            } else if (ev.value == 1) {
                pressed_or_hold = 1;
            }
            else if (ev.value == 2) {
                pressed_or_hold = 1;
            }
            if (pressed_or_hold) {
                if (0 <= ev.code && ev.code < 256 && pressed_keys[ev.code] == 0) {
                    pressed_keys[ev.code] = 1;
                    total_pressed_keys++;
                }
                for (int i = 0; i < sizeof(shortcuts) / sizeof(shortcuts[0]); i++) {
                    Shortcut sc = shortcuts[i];
                    int all_pressed = 1;
                    for (int j = 0; j < sc.keys_len; j++) {
                        if (pressed_keys[sc.keys[j]] == 0) {
                            all_pressed = 0;
                            break;
                        }
                    }
                    if (all_pressed && total_pressed_keys == sc.keys_len) {
                        printf("%s\n", sc.message);
                        fprintf(fout, "%s\n", sc.message);
                        fflush(fout);
                    }
                }
            }
        }
    }

    close(fd);
    fclose(fout);
    fflush(stdout);
    exit(EXIT_FAILURE);
}
