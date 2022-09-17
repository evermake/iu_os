#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define N 5

/*
 * Return current year (by local time).
 *
 * Code is taken from:
 * stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program
*/
int get_current_year() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year + 1900;
}

int foo(int age) {
    return get_current_year() - age;
}

int main() {
    const int x = 10, *q = &x;
    const int *const p = malloc(sizeof(const int) * N);
    for (int i = 0; i < N; i++) {
        int *p_i = (int*) (p+i);
        *p_i = x;
        printf("%p\n", p_i);
    }

    for (int i = 0; i < N; i++) {
        int *p_i = (int*) (p+i);
        int age;
        scanf("%d", &age);
        *p_i = age;
    }

    for (int i = 0; i < N; i++) {
        int *p_i = (int*) (p+i);
        *p_i = foo(*p_i);
    }

    free((void*) p);
}
