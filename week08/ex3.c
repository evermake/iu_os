#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define N 10
#define _10MB (1024*1024*10)

/**
 * After running the program and `top -i 1 -o mem`,
 * I've find that the amount of occupied memory
 * of the program ex2 was increasing from 10+MB until
 * 100+MB, then the process had disappeared.
 *
 * This confirms that program uses 10MB more memory
 * each second and terminates after 10 seconds.
 */
int main() {
    for (int i = 0; i < N; i++) {
        void* ptr = malloc(_10MB);
        memset(ptr, 0, _10MB);
        sleep(1);
    }
}
