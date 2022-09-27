#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#define DEBUG false
#define VECTOR_SIZE 120
#define TEMP_FILE_NAME "temp.txt"

typedef int vector[VECTOR_SIZE];

/*
 * Return (pseudo) random integer within range [0,99].
 */
int get_random_value() {
    return rand() % 100;
}

void fill_vector_with_random_values(vector v) {
    for (int i = 0; i < VECTOR_SIZE; i++) {
        v[i] = get_random_value();
    }
}

void print_vector(vector v) {
    printf("[");
    for (int i = 0; i < VECTOR_SIZE - 1; i++) {
        printf("%d, ", v[i]);
    }
    printf("%d]\n", v[VECTOR_SIZE-1]);
}

/*
 * Write workers result to the file.
 */
void worker_write_int_to_file(int val, FILE* f) {
    fprintf(f, "_%d_", val);
}

/*
 * Calculate products of worker's elements and
 * write them to the file.
 */
void worker_dot_product_partition_to_file(
    vector a,
    vector b,
    int offset,
    int count,
    FILE* f
) {
    int sum = 0;
    for (int i = offset; i < offset+count; i++) {
        sum += a[i] * b[i];
    }
    worker_write_int_to_file(sum, f);
}

/*
 * Read all content of the file to allocated string and return it.
 */
char *const read_file_content(FILE* f) {
    // Get file size
    fseek(f, 0, SEEK_END);
    size_t len = ftell(f);
    rewind(f);

    // Allocate memory for file content
    char *const content = malloc(len + 1);
    if (content == NULL) {
        fprintf(stderr, "failed to allocate memory for file content (%d)\n", errno);
        exit(11);
    }

    // Read file content
    size_t read_size = fread(content, 1, len, f);
    if (read_size != len) {
        fprintf(stderr, "failed to read file content (%d)\n", errno);
        exit(12);
    }

    // Terminate string
    content[len] = '\0';

    return content;
}

/*
 * Read the file with workers' results and return their sum.
 */
long long sum_numbers_from_worker_files(FILE* f) {
    // Read file content to string
    char *const content = read_file_content(f); 

    char* s = content;
    long long sum = 0;
    bool moved = true;
    while (moved) {
        moved = false;
        // Skip underscores
        for (; *s == '_'; s++)
            moved = true;

        sum += atoi(s);

        // Skip digits
        for (; '0' <= *s && *s <= '9'; s++)
            moved = true;
    }

    free(content);

    return sum;
}

/*
 * Calculate dot product of vectors a and b spawning n processes.
 */
long long dot_product_multiprocess(
    vector a,
    vector b,
    const int n
) {
    if (n < 1 || n > VECTOR_SIZE) exit(123);

    FILE* tmp_file = fopen(TEMP_FILE_NAME, "w");

    if (tmp_file == NULL) {
        fprintf(stderr, "failed to open temporary file (%d)\n", errno);
        exit(10);
    }

    int elements_per_worker = VECTOR_SIZE / n;
    pid_t elements_pids[20];
    pid_t fork_pid;

    int offset = 0;
    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            // Last worker
            elements_per_worker += VECTOR_SIZE % n;
        }

        fork_pid = fork();
        if (fork_pid == 0) {
            // Worker code
            worker_dot_product_partition_to_file(
                a,
                b,
                offset,
                elements_per_worker,
                tmp_file
            );
            exit(0);
        }
        // Main process
        elements_pids[i] = fork_pid;
        offset += elements_per_worker;
    }

    // Wait until processes finish
    for (int i = 0; i < n; i++) {
        if (DEBUG) printf("Waiting for process #%d to finish...", i+1);
        waitpid(elements_pids[i], NULL, WCONTINUED);
        if (DEBUG) printf("Done!\n");
    }

    fclose(tmp_file);
    tmp_file = fopen(TEMP_FILE_NAME, "r");
    long long product = sum_numbers_from_worker_files(tmp_file);
    fclose(tmp_file);
    return product;
}

int main() {
    srand(time(NULL));  // Set seed for random generator

    vector u, v;

    fill_vector_with_random_values(u);
    fill_vector_with_random_values(v);

    if (DEBUG) {
        printf("u = ");
        print_vector(u);
        printf("\n");

        printf("v = ");
        print_vector(v);
        printf("\n");
    }

    int n;
    while (true) {
        printf("Enter the number of processes (1-10): ");
        fflush(stdout);
        scanf("%d", &n);
        if (1 <= n && n <= 10) {
            break;
        }
    }

    long long dot_product = dot_product_multiprocess(u, v, n);

    printf("u • v = %lld\n", dot_product);
}
