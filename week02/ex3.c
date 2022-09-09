#include <stdio.h>
#include <stdlib.h>

void panic() {
    printf("cannot convert!\n");
    exit(1);
}

long long convert_to_decimal(long long n, int from) {
    long long result = 0;
    long long multiplier = 1;
    long long d;
    while (n != 0) {
        d = n % 10;
        if (d >= from) panic();
        result += d * multiplier;
        n /= 10;
        multiplier *= from;
    }
    return result;
}

long long convert_from_decimal(long long n, int to) {
    long long result = 0;
    long long multiplier = 1;
    long long d;
    while (n != 0) {
        d = n % to;
        result += d * multiplier;
        n /= to;
        multiplier *= 10;
    }
    return result;
}

void convert(long long n, int source, int target) {
    if (source < 2 || source > 10) panic();
    if (target < 2 || target > 10) panic();

    n = convert_to_decimal(n, source);
    n = convert_from_decimal(n, target);

    printf("%lld\n", n);
}

int main() {
    long long x;
    int a, b, read;

    printf("Convert X from A to B\n");

    printf("Enter X: ");
    read = scanf("%lld", &x);
    if (read != 1 || x < 0) panic();

    printf("Enter A: ");
    read = scanf("%d", &a);
    if (read != 1) panic();

    printf("Enter B: ");
    read = scanf("%d", &b);
    if (read != 1) panic();

    convert(x, a, b);
}
