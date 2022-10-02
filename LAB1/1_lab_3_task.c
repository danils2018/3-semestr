#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int entered_parameters_verify(int argc, char** argv) {
    if (argc <= 1) {
        printf("Parameters no entered!\n");
        return 0;
    }
    int i, k = 0;
    for (i = 0; argv[1][i] != '\0'; ++i) {
        k++;
    }
    if (!(k == 2 || k == 3)) {
        printf("Flag entered incorrectly! (must be length 2 or 3)\n");
        return 0;
    }
    return 1;
}
int symbol_is_bukva(char c)
{
    return (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z');
}

char to_floor(char c)
{
    if(symbol_is_bukva(c)){
        if (c >= 'A' && c <= 'Z') return (c + 32); //с русскими буквами проблема с кодировками (всё перепробовал, у меня не робит с русскими)
        else return c;
    } else {
        return c;
    }
}

int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int main(int argc, char *argv[]) {

    int i;
    char c;
    int b, k_in_string; //for -i
    int good_flag = 0, ERRORS = 1;

    ERRORS = entered_parameters_verify(argc, argv); // проверка на длину флага и введены ли параметры вообще
    if (!(ERRORS)) {
        return 0;
    }
    if(argv[1][1] == 'n' && argc == 3) {
        printf("You need the path of the file where you want to output (3rd argument)\n");
        return 0;
    }


    FILE* input_file = fopen(argv[2], "r");

    if (input_file == NULL) {
        printf("Error opening input file %s\n");
        return 0;
    }

    char* output; //
    if (argc == 4 && strcmp(argv[2], argv[3])) {
        output = malloc(sizeof(char) * (strlen(argv[3])));
        output = argv[3];
    } else {
        int j = 0, ukazatel_na_slash = -1;
        int len_argv_2 = strlen(argv[2]);
        output = malloc(sizeof(char) * (len_argv_2 + 4));
        for (j = len_argv_2 - 1; j >= 0; --j) {
            if (argv[2][j] == '\\') {
                ukazatel_na_slash = j;
                break;
            }
        }

        for (j = 0; j <= ukazatel_na_slash; ++j) {
            output[j] = argv[2][j];
        }

        int kk = 0;
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
                output[j] = argv[2][j - 4];
            }
        }
    }
    //генерация названия выходного файла.


    FILE* output_file;
    if(argc == 4) {
        output_file = fopen(output, "r+");
    } else {
        output_file = fopen(output, "w");
    }
    if (output_file == NULL) {
        printf("Error opening output file %s\n");
        return 0;
    }


    int help_flag = 1;
    char parametrs [20][4] = {"-d", "/d", "-i", "/i", "-s", "/s", "-a", "/a", "-f", "/f", "-nd", "/nd", "-ni", "/ni", "-ns", "/ns", "-na", "/na", "-nf", "/nf"};
    for (i = 0; i < 20; i += 2) {
        if (!strcmp(parametrs[i], argv[1]) || !strcmp(parametrs[i + 1], argv[1])) {
            good_flag = 1;
            if (i > 9) {
                help_flag = 2;
            }
            switch (parametrs[i][help_flag]) {
                case 'd':
                    while((c = fgetc(input_file)) != EOF) {
                        if (!(is_digit(c))) {
                           fprintf(output_file, "%c", c);
                        }
                    }
                    break;
                case 'i':
                    b = 1;
                    k_in_string = 0;
                    while((c = fgetc(input_file)) != EOF) {
                        if(!k_in_string) {
                            fprintf(output_file, "%d - ", b);
                            k_in_string++;
                        }
                        if (symbol_is_bukva(c)) {
                            k_in_string++;
                        } else if(c == '\n') {
                            fprintf(output_file, "%d\n", k_in_string - 1);
                            k_in_string = 0;
                            b++;
                        }
                    }
                    fprintf(output_file, "%d\n", k_in_string - 1);
                    break;
                case 's':
                    b = 1;
                    k_in_string = 0;
                    while((c = fgetc(input_file)) != EOF) {
                        if(!k_in_string) {
                            fprintf(output_file, "%d - ", b);
                            k_in_string++;
                        }
                        if (!symbol_is_bukva(c) && !is_digit(c) && c != ' ' && c != '\n') {
                            k_in_string++;
                        } else if(c == '\n') {
                            fprintf(output_file, "%d\n", k_in_string - 1);
                            k_in_string = 0;
                            b++;
                        }
                    }
                    fprintf(output_file, "%d\n", k_in_string - 1);
                    break;
                case 'a':
                    while((c = fgetc(input_file)) != EOF) {
                        if (!(is_digit(c))) {
                            fprintf(output_file, "%d", c);
                        } else {
                            fprintf(output_file, "%c", c);
                        }
                    }
                    break;
                case 'f':
                    k_in_string = 1;
                    while((c = fgetc(input_file)) != EOF) {
                        if(c == '\n' || c == ' ') {
                            fprintf(output_file, "%c", c);
                            k_in_string++;
                        } else if(k_in_string % 10 == 0){
                            fprintf(output_file, "%d", to_floor(c));
                        } else if(k_in_string % 5 == 0){
                            fprintf(output_file, "%d", c);
                        } else if (k_in_string % 2 == 0) {
                            fprintf(output_file, "%c", to_floor(c));
                        }  else {
                            fprintf(output_file, "%c", c);
                        }
                    }
                    break;
            }
        }
    }
    if(!good_flag) {
        printf("Invalid flag entered! (Flag start in '-' or '/' and then one of the 'disaf' or with insert n before 'disaf')\n");
    }


    free(output);
    fclose(input_file);
    fclose(output_file);
    return 0;
}
