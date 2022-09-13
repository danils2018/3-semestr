#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int to_cc(char c)
{
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    else if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    else if (c >= '0' && c <= '9') return c - '0';
    else return -1;
}

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
    int i = 0;

    // генерация названия файла.
    char* output;
    int j = 0, ukazatel_na_slash = -1;
    int len_argv_2 = strlen(argv[1]);
    output = malloc(sizeof(char) * (len_argv_2 + 4));
    for (j = 0; j < len_argv_2; j++) {
        if (argv[1][j] == '\\') {
            ukazatel_na_slash = j;
        }
    }

    for (j = 0; j <= ukazatel_na_slash; j++) {
        output[j] = argv[1][j];
    }


    for (j = ukazatel_na_slash + 1; j < len_argv_2 + 4; j++) {
        int l = j - (ukazatel_na_slash + 1);
        if (l == 0) {
            output[j] = 'o';
        } else if (l == 1) {
            output[j] = 'u';
        } else if (l == 2) {
            output[j] = 't';
        } else if (l == 3) {
            output[j] = '_';
        } else {
            output[j] = argv[1][j - 4];
        }
    }

    FILE* output_file = fopen(output, "w");


    char array[50]; //сюда должно влезать число в какой-то системе счисления.
    int flag = 0;
    int max = 0;
    while ((c = fgetc(input_file))) {
        if (c != ' ' && c != '\n' && c != EOF) {
            array[i] = c;
            if(to_cc(c) == -1) {
                printf("File contains invalid characters...");
                return 0;
            }
            if (to_cc(c) > max) {max = to_cc(c);}
            fprintf(output_file, "%c", c);
            flag = 0;
            i++;
        } else if (flag == 0) {
            fprintf(output_file, " - minimum number system: %d  =>  ", max + 1);

            long long p = 1, result = 0;
            for(int l = i - 1; l >= 0; l --){
                result += (p * to_cc(array[l]));
                p *= (max + 1);
            }
            fprintf(output_file, "%lld\n", result);
            flag = 1;
            max = 0;
            i = 0;
            if (c == EOF) break;
        }
    }

    fclose(input_file);
    fclose(output_file);




    return 0;
}
