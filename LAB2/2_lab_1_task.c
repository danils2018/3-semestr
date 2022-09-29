#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double *generate_matrix(int *n) {
    *n = rand() % 19 + 1;

    double *matrix = (double*)malloc(sizeof(double) * *n);
    for (int i = 0; i < *n; i++) {
        matrix[i] = rand() % 200 - 100;
    }

    return matrix;
}

void output_matrix(double *matrix, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.1lf ", matrix[i]);
    }
    printf("\n");
}



double *result_matrix(double *matrix_1, int n1, double *matrix_2, int n2) {
    double *result = NULL;

    result = (double*)malloc(sizeof(double*) * n1);

    for (int i = 0; i < n1; i++) {
        result[i] = matrix_1[i] + ((i >= n2) ? matrix_2[n2 - 1] : matrix_2[i]);
    }

    return result;
}


int main() {
    srand(time(0));
    int n1 = 0;
    int n2 = 0;
    double *matrix_1 = generate_matrix(&n1);
    double *matrix_2 = generate_matrix(&n2);

    printf("A:\n");
    output_matrix(matrix_1, n1);
    printf("B:\n");
    output_matrix(matrix_2, n2);

    printf("C:\n");
    double *matrix_3 = result_matrix(matrix_1, n1, matrix_2, n2);
    output_matrix(matrix_3, n1);



    free(matrix_1);
    free(matrix_2);
    free(matrix_3);
    return 0;
}