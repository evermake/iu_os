#include <stdio.h>
#include <stdlib.h>


void* aggregate(void* base, size_t size, int n, void* initial_value, void* (*opr)(const void*, const void*));

void* sumInt(const void* a, const void* b) {
    int* z = (int*) malloc(sizeof(int));
    *z = *((int*)a) + *((int*)b);
    return z;
}

void* sumDouble(const void* a, const void* b) {
    double* z = (double*) malloc(sizeof(double));
    *z = *((double*)a) + *((double*)b);
    return z;
}

void* multiplyInt(const void* a, const void* b) {
    int* z = (int*) malloc(sizeof(int));
    *z = *((int*)a) * *((int*)b);
    return z;
}

void* multiplyDouble(const void* a, const void* b) {
    double* z = (double*) malloc(sizeof(double));
    *z = *((double*)a) * *((double*)b);
    return z;
}

void* meanInt(const void* a, const void* b) {
    int* z = (int*) malloc(sizeof(int));
    *z = (*((int*)a) + *((int*)b)) / 2;
    return z;
}

void* meanDouble(const void* a, const void* b) {
    double* z = (double*) malloc(sizeof(double));
    *z = (*((double*)a) + *((double*)b)) / 2;
    return z;
}

void* aggregate(
    void* base,
    size_t size,
    int n,
    void* initial_value,
    void* (*opr)(const void*, const void*)
) {
	void* output;

	if (size == sizeof(int)) { // base is a pointer to an integer
        output = malloc(sizeof(int));

        int* base_int = (int*) base;
        int* output_int = (int*) initial_value;
        for (int i = 0; i < n; i++) {
            int* allocated_result = (int*) opr(output_int, base_int + i);
            *output_int = *allocated_result;
            free((void*)allocated_result);
        }
        *((int*)output) = *output_int;
	} else { // base is a pointer to a double
        output = malloc(sizeof(double));

        double* base_double = (double*) base;
        double* output_double = (double*) initial_value;
        for (int i = 0; i < n; i++) {
            double* allocated_result = (double*) opr(output_double, base_double + i);
            *output_double = *allocated_result;
            free((void*)allocated_result);
        }
        *((double*)output) = *output_double;
	}

	return output;
}


int main(){
    int* ints = malloc(sizeof(int)*5);
    double* doubles = malloc(sizeof(double)*5);

    ints[0] = 1;
    ints[1] = -10;
    ints[2] = -4321;
    ints[3] = 15;
    ints[4] = 100;

    doubles[0] = 5.25;
    doubles[1] = -10.5;
    doubles[2] = 0.01;
    doubles[3] = 20.2;
    doubles[4] = 100.0;

    // Addition
    int initial_val_sum_ints = 0;
    int* ints_sum = aggregate(
        ints,
        sizeof(int),
        5,
        (void*)(&initial_val_sum_ints),
        sumInt
    );
    printf("%d\n", *ints_sum);

    double initial_val_sum_doubles = 0.0;
    double* doubles_sum = aggregate(
        doubles,
        sizeof(double),
        5, (void*)(&initial_val_sum_doubles),
        sumDouble
    );
    printf("%f\n", *doubles_sum);

    // Multiplication
    int initial_val_multiply_ints = 1;
    int* ints_product = aggregate(
        ints,
        sizeof(int),
        5, (void*)(&initial_val_multiply_ints),
        multiplyInt
    );
    printf("%d\n", *ints_product);

    double initial_val_multiply_doubles = 1.0;
    double* doubles_product = aggregate(
        doubles,
        sizeof(double),
        5, (void*)(&initial_val_multiply_doubles),
        multiplyDouble
    );
    printf("%f\n", *doubles_product);

    // Mean
    int initial_val_mean_ints = 0;
    int* ints_mean = aggregate(
        ints,
        sizeof(int),
        5, (void*)(&initial_val_mean_ints),
        meanInt
    );
    printf("%d\n", *ints_mean);

    double initial_val_mean_doubles = 0.0;
    double* doubles_mean = aggregate(
        doubles,
        sizeof(double),
        5, (void*)(&initial_val_mean_doubles),
        meanDouble
    );
    printf("%f\n", *doubles_mean);

    free(ints_sum);
    free(doubles_sum);
    free(ints_product);
    free(doubles_product);
    free(ints_mean);
    free(doubles_mean);
    
    free(ints);
    free(doubles);

    return EXIT_SUCCESS;
}
