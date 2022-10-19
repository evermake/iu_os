#include <stdlib.h>
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    if (n <= 0) return 1;
    int* nums = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        nums[i] = i;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
    free(nums);
    return 0;
}

