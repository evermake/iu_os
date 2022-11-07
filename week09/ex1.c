#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_FILE "input.txt"
#define AGE_BITS 16

typedef struct {
    int page;
    int age;
} Page;

// With page frames = 10, hits/misses: 10/990 = 0.010101
// With page frames = 50, hits/misses: 17/983 = 0.017294
// With page frames = 100, hits/misses: 17/983 = 0.017294
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number of page frames>\n", argv[0]);
        return 1;
    }

    int page_frames = atoi(argv[1]);

    if (page_frames <= 0) {
        printf("Invalid number of page frames: %d\n", page_frames);
        return 1;
    }

    Page *pages = malloc(page_frames * sizeof(Page));
    for (int i = 0; i < page_frames; i++) {
        pages[i].page = -1;
        pages[i].age = 0;
    }

    FILE *input = fopen(INPUT_FILE, "r");
    if (input == NULL) {
        printf("Error opening file %s\n", INPUT_FILE);
        return 1;
    }

    int requested_page;
    int hits = 0;
    int misses = 0;
    while (fscanf(input, "%d", &requested_page) != EOF) {
        // Aging
        for (int i = 0; i < page_frames; i++) {
            pages[i].age = pages[i].age >> 1;
        }

        // Try to find in page frames
        bool found = false;
        for (int i = 0; i < page_frames; i++) {
            if (pages[i].page == requested_page) {
                found = true;
                hits++;
                pages[i].age = (pages[i].age >> 1) | (1 << (AGE_BITS - 2));
                break;
            }
        }

        // Should swap
        if (!found) {
            misses++;
            int min_age = pages[0].age;
            int min_age_i = 0;
            for (int i = 1; i < page_frames; i++) {
                if (pages[i].age < min_age) {
                    min_age = pages[i].age;
                    min_age_i = i;
                }
            }

            pages[min_age_i].page = requested_page;
            pages[min_age_i].age = (pages[min_age_i].age >> 1) | (1 << (AGE_BITS - 2));
        }
    }

    printf("hits/misses: %d/%d = %f\n", hits, misses, (double) hits / misses);

    free(pages);
    fclose(input);
    return 0;
}
