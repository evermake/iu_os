#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct {
    float x, y;
} Point;

float distance(Point* A, Point* B) {
    return sqrt(
        pow(A->x - B->x, 2) +
        pow(A->y - B->y, 2)
    );
}

float area(Point* A, Point* B, Point* C) {
    return 0.5 * fabs(
        (A->x * B->y) -
        (B->x * A->y) +
        (B->x * C->y) -
        (C->x * B->y) +
        (C->x * A->y) -
        (A->x * C->y)
    );
}

int main() {
    Point A = {.x = 2.5,  .y = 6.0};
    Point B = {.x = 1.0,  .y = 2.2};
    Point C = {.x = 10.0, .y = 6.0};

    printf("Points:\n");
    printf("  A(%f, %f)\n", A.x, A.y);
    printf("  B(%f, %f)\n", B.x, B.y);
    printf("  C(%f, %f)\n", C.x, C.y);

    printf("------------------------------\n");

    float ab = distance(&A, &B);
    printf("Distance between A and B is %f\n", ab);

    float area_abc = area(&A, &B, &C);
    printf("Area of the triangle ABC is %f\n", area_abc);
}
