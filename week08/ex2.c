#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define N 10
#define _10MB (1024*1024*10)

/**
 * After running the program and vm_stat 1 the number of
 * free pages decreases each second by at least 640, and
 * the number of 0-filled pages increases at least by 640.
 * This happens, because the program requests 10MB/(page size),
 * each second, and since on my machine page size 16KB,
 * the program requests and fills with zeros 640 pages.
 * After 10 seconds the number of free pages has increased,
 * because pages used by the program were freed by OS.
 *
 * The number of swapins and swapouts were always 0.
 * I guess this is because I have no many open programs,
 * therefore there is enough space in RAM to hold all the data
 * or there are pages in swap that were not requested during test.
 */
int main() {
    for (int i = 0; i < N; i++) {
        void* ptr = malloc(_10MB);
        memset(ptr, 0, _10MB);
        sleep(1);
    }
}
