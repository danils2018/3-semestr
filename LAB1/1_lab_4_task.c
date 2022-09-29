#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

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

    //int n;
    int i, n = 10;

    char** matrix = (char**) malloc(sizeof(char*) * 3);

    for(i = 0; i < 3; i ++)
    {
        matrix[i] = (char*) malloc(sizeof(char) * n);
    }


    // генерация названия файла.
    char* output;
    int j, ukazatel_na_slash = -1;
    output = malloc(sizeof(char) * 300);
    for (j = 0; argv[0][j] != '\0'; j++) {
        if (argv[0][j] == '\\') {
            ukazatel_na_slash = j;
        }
    }

    for (j = 0; j <= ukazatel_na_slash; j++) {
        output[j] = argv[0][j];
    }
    strcpy(output, "out.txt");


    FILE* output_file = fopen(output, "w");
    if (output_file == NULL) {
        printf("Error opening output file\n");
        return 0;
    }
    i = 0, j = 0;
    char ch, _c = 0;
    while (!feof(input_file)) {
        ch = fgetc(input_file);
        if (!isspace(ch)) {
            if(j >= n) {
                n += 128;
                matrix[i] = realloc(matrix[i], n);
            }
            matrix[i][j] = ch;
            j++;
        } else if (isspace(ch) && !isspace(_c)){
            if(j >= n) {
                n += 128;
                matrix[i] = realloc(matrix[i], n);
            }
            matrix[i][j] = '\0';
            i++;
            if (i == 3) {
                for (int k = 0; k < 3; ++k){
                    fprintf(output_file, "%s ", matrix[(k + 2) % 3]);
                }
                fprintf(output_file, "\n");
                i = 0;
            }
            j = 0;
        }
        _c = ch;
    }
    for(i = 0; i < 3; i ++)
    {
        free(matrix[i]);
    }
    free(matrix);

    fclose(input_file);
    fclose(output_file);

    input_file = fopen(output, "r");
    output_file = fopen(argv[1], "w");

    char c;
    while((c = getc(input_file)) != EOF) {
        fprintf(output_file, "%c", c);
    }
    fclose(input_file);
    fclose(output_file);

    remove(output);
    return 0;
}
