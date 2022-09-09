#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    int i;
    unsigned short int usi;
    signed long int sli;
    float f;
    double d;

    i = INT_MAX;
    usi = USHRT_MAX;
    sli = LONG_MAX;
    f = FLT_MAX;
    d = DBL_MAX;

    printf("sizeof i   = %lu bytes\n", sizeof i);
    printf("       i   = %d\n", i);
    printf("\n");
    printf("sizeof usi = %lu bytes\n", sizeof usi);
    printf("       usi = %hu\n", usi);
    printf("\n");
    printf("sizeof sli = %lu bytes\n", sizeof sli);
    printf("       sli = %lu\n", sli);
    printf("\n");
    printf("sizeof f   = %lu bytes\n", sizeof f);
    printf("       f   = %f\n", f);
    printf("\n");
    printf("sizeof d   = %lu bytes\n", sizeof d);
    printf("       d   = %f\n", d);
}
