#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int ** matr(int ** a, int n, int x){
    int ** res = (int **)malloc((n - 1) * sizeof(int *));
    for (int i = 0; i < n - 1; ++i)
        res[i] = (int *)malloc((n - 1) * sizeof(int));
    for (int i = 1; i < n; ++i)
        for (int j = 0, k = 0; j < n; ++j, ++k){
            if (j == x){
                --k;
                continue;
            }
            res[i - 1][k] = a[i][j];
        }
    return res;
}

long long determinant(int ** a, int n){
    if (n == 1)
        return a[0][0];
    if (n == 2)
        return (a[1][1] * a[0][0]) - (a[0][1] * a[1][0]);
    long long ans = 0, sig = 1;
    for (int i = 0; i < n; ++i){
        ans += (sig * a[0][i] * determinant(matr(a, n, i),n - 1));
        sig *= -1;
    }
    return ans;
}


int main(int argc, char *argv[]) {
    srand(time(0));
    int n = 1 + rand() % 10, m = 1 + rand() % 10;
    int n2 = 1 + rand() % 10, m2 = 1 + rand() % 10;
    //n = 10; m = 10; n2 = 10; m2 = 10;
    int i, j, k, z;

    char parametrs [3][3] = {"a)", "b)", "c)"};

    int good_flag = 0;
    for (k = 0; k < 5; k++) {
        if (!strcmp(parametrs[k], argv[1])) {
            good_flag = 1;
            switch (parametrs[k][0]) {
                case 'a':
                    printf("\nMatrix:\n");
                    int** matrix = (int**) malloc(sizeof(int*) * n);
                    for(i = 0; i < n; i ++)
                    {
                        matrix[i] = (int*) malloc(sizeof(int) * m);
                        for (j = 0; j < m; j++)
                        {
                            matrix[i][j] = rand() % 101 * (rand() % 2 == 0 ? -1 : 1);
                            printf("%d ", matrix[i][j]);
                        }
                        printf("\n");
                    }

                    for(i = 0; i < n; i ++)
                    {
                        free(matrix[i]);
                    }

                    free(matrix);

                    break;
                case 'b':
                    printf("\nMatrix 1:\n");
                    int** matrix1 = (int**) malloc(sizeof(int*) * n);

                    for(i = 0; i < n; i ++)
                    {
                        matrix1[i] = (int*) malloc(sizeof(int) * m);
                        for (j = 0; j < m; j++)
                        {
                            matrix1[i][j] = rand() % 101 * (rand() % 2 == 0 ? -1 : 1);
                            printf("%d ", matrix1[i][j]);
                        }
                        printf("\n");
                    }

                    printf("\nMatrix 2:\n");
                    int** matrix2 = (int**) malloc(sizeof(int*) * n2);
                    for(i = 0; i < n2; i ++)
                    {
                        matrix2[i] = (int*) malloc(sizeof(int) * m2);
                        for (j = 0; j < m2; j++)
                        {
                            matrix2[i][j] = rand() % 101 * (rand() % 2 == 0 ? -1 : 1);
                            printf("%d ", matrix2[i][j]);
                        }
                        printf("\n");
                    }
                    printf("\n");
                    if(m != n2) {
                        printf("Unfortunately, we can`t multiply these matrices!\n");
                        return 0;
                    }

                    int** matrix3 = (int**) malloc(sizeof(int*) * n);
                    for(i = 0; i < n; i ++)
                    {
                        matrix3[i] = (int*) malloc(sizeof(int) * m2);
                        for (j = 0; j < m2; j++)
                        {
                            matrix3[i][j] = 0;
                        }
                    }

                    for(i = 0; i < n; i++)
                    {
                        for(j = 0; j < m2; j++)
                        {
                            for(z = 0; z < m; z++)
                                matrix3[i][j] += matrix1[i][z] * matrix2[z][j];
                        }
                    }

                    printf("Result matrix:\n");

                    for(i = 0; i < n; i ++)
                    {
                        for (j = 0; j < m2; j++)
                        {
                            printf("%d ", matrix3[i][j]);
                        }
                        printf("\n");
                    }






                    for(i = 0; i < m; i ++)
                    {
                        free(matrix1[i]);
                    }
                    free(matrix1);
                    for(i = 0; i < m2; i ++)
                    {
                        free(matrix2[i]);
                        free(matrix3[i]);
                    }
                    free(matrix2);
                    free(matrix3);
                    break;
                case 'c':
                    printf("\nMatrix 1:\n");
                    int** Matrix1 = (int**) malloc(sizeof(int*) * n);

                    for(i = 0; i < n; i ++)
                    {
                        Matrix1[i] = (int*) malloc(sizeof(int) * m);
                        for (j = 0; j < m; j++)
                        {
                            Matrix1[i][j] = rand() % 101 * (rand() % 2 == 0 ? -1 : 1);
                            printf("%d ", Matrix1[i][j]);
                        }
                        printf("\n");
                    }
                    if (n != m) {
                        printf("\nUnable to calculate determinant!\n");
                    } else {
                        printf("\nDeterminant: %lld\n",determinant(Matrix1, n));
                    }

                    printf("\nMatrix 2:\n");
                    int** Matrix2 = (int**) malloc(sizeof(int*) * n2);
                    for(i = 0; i < n2; i ++)
                    {
                        Matrix2[i] = (int*) malloc(sizeof(int) * m2);
                        for (j = 0; j < m2; j++)
                        {
                            Matrix2[i][j] = rand() % 101 * (rand() % 2 == 0 ? -1 : 1);
                            printf("%d ", Matrix2[i][j]);
                        }
                        printf("\n");
                    }
                    if (n2 != m2) {
                        printf("\nUnable to calculate determinant!\n");
                    } else {
                        printf("\nDeterminant: %lld\n",determinant(Matrix2, n2));
                    }

                    for(i = 0; i < m; i ++)
                    {
                        free(Matrix1[i]);
                    }
                    free(Matrix1);
                    for(i = 0; i < m2; i ++)
                    {
                        free(Matrix2[i]);
                    }
                    free(Matrix2);

                    break;
            }
        }
    }
    if(!good_flag) {
        printf("Invalid flag entered! flag one of the ( 'a)' , 'b)', 'c)', 'd)', 'e)' )\n");
        return 0;
    }
    return 0;
}
