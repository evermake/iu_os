#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

#define _10MB (1024*1024*10)

int main() {
    struct rusage usage;
    int i;
    for (i = 0; i < 10; i++) {
        char *p = malloc(_10MB);
        memset(p, 0, _10MB);
        getrusage(RUSAGE_SELF, &usage);
        printf("Memory usage: %ld\n", usage.ru_maxrss);
        sleep(1);
    }
    return 0;
}
