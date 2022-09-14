#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Please, input path to the file");
        return 0;
    } else if (argc > 2) {
        printf("Сheck the correctness of the entered data");
        return 0;
    }

    FILE* input_file = fopen(argv[1], "r");

    if (input_file == NULL) {
        printf("Error opening input file\n");
        return 0;
    }
    char c;
    int n = 1;
    int i, j, k, kk = 0;
    int max_str = 0;
    while (c = fgetc(input_file)) {
        if (c == '\n'|| c == EOF) n++;
        else if (c != ' ' && c != '\n' && c != EOF) {
            kk ++;
        } else {if (kk > max_str) max_str = kk; kk = 0;}
        if(c == EOF) break;
    }
    fclose(input_file);

    input_file = fopen(argv[1], "r");
    char*** matrix = (char***) malloc(sizeof(char**) * n);

    for(i = 0; i < n; i ++)
    {
        matrix[i] = (char**) malloc(sizeof(char*) * 3);
    }
    for(i = 0; i < n; i ++)
    {
        for(j = 0; j < 3; j ++)
        matrix[i][j] = (char*) malloc(sizeof(char) * max_str);
    }
    i = 0;
    j = 0;
    k = 0;
    int flag = 0;
    while ((c = fgetc(input_file))) {
        if (c != ' ' && c != '\n' && c != EOF) {
            matrix[i][j][k] = c;
            k++;
            flag = 0;
        } else if (c == ' ' && flag == 0){
            matrix[i][j][k] = ' ';
            flag = 1;
            k = 0;
            j++;
        } else if (c == '\n') {
            if (flag == 0) {
                matrix[i][j][k] = ' ';
            } else {
                flag = 1;
            }
            i ++;
            j = 0;
            k = 0;
        } else if (c == EOF) {
            if (flag == 0) {
                matrix[i][j][k] = ' ';
            } else {
                flag = 1;
            }
            break;
        }

    }

    fclose(input_file);
    FILE* output_file = fopen(argv[1], "w");
    if (output_file == NULL) {
        printf("Error opening output file\n");
        return 0;
    }

    for (int i1 = 0; i1 < n; i1 ++) {
        for (int i2 = 0; i2 < 3; i2 ++) {
            for (int i3 = 0; i3 < max_str; i3 ++)
            {
                fprintf(output_file, "%c", matrix[i1][(i2 + 2) % 3][i3]);
                if (matrix[i1][(i2 + 2) % 3][i3] == ' ') break;
            }
        }
        fprintf(output_file, "\n");
    }

    for(i = 0; i < n; i ++)
    {
        for(j = 0; j < 3; j ++)
            free(matrix[i][j]);
    }
    for(i = 0; i < n; i ++)
    {
        free(matrix[i]);
    }
    free(matrix);
    fclose(output_file);
    return 0;
}
