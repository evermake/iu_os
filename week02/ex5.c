#include <stdio.h>

int tribonacci(int n) {
    int t1 = 0;
    int t2 = 0;
    int t3 = 0;
    for (int i = 0; i < n; i++) {
        if (t1 == 0) {
            t1 = 1;
            continue;
        }
        int new = t1 + t2 + t3;
        t3 = t2;
        t2 = t1;
        t1 = new;
    }
    return t1;
}

int main() {
    printf("%d\n", tribonacci(4));
    printf("%d\n", tribonacci(36));
}
