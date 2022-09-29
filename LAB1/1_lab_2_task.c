#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

double eps = 0.0000000001;

int conv_n_to_int(char* s, int* check_error_in_numbers){
    int i, minus = 0, k = 0;
    int n = 0;
    for (i = 0; s[i] != '\0'; ++i) {
        if (i == 0) {
            if (s[i] == '-') {
                minus = 1;
            } else if (s[i] == '+') {
                *check_error_in_numbers = -1;
            } else if (s[i] >= '0' && s[i] <= '9') {
                n = n * 10 + (s[i] - '0');
                k = 1;
            } else {
                *check_error_in_numbers = -2;
                break;
            }
        } else {
            if (s[i] >= '0' && s[i] <= '9') {
                n = n * 10 + (s[i] - '0');
                k = 1;
            } else {
                *check_error_in_numbers = -2;
                break;
            }
        }
    }
    if (minus) {
        n = -n;
    }
    if (n == 0) {
        *check_error_in_numbers = -4;
    }
    if (k == 0){
        *check_error_in_numbers = -3;
    }
    return n;
} //Здесь коды ошибок кладутся в чек ерор и одновременно с этим переводится число из строки в int

double conv_to_double(char *s, int* check_error_in_numbers) {
    int i, minus = 0, k = 0, k_dots = 0;
    double n1 = 0, n2 = 0;
    for (i = 0; s[i] != '\0'; ++i) {
        if (i == 0) {
            if (s[i] == '-') {
                minus = 1;
            } else if (s[i] == '+') {
                *check_error_in_numbers = -1;
            } else if (s[i] >= '0' && s[i] <= '9') {
                n1 = n1 * 10 + (s[i] - '0');
                k = 1;
            } else {
                *check_error_in_numbers = -2;
                break;
            }
        } else {
            if (s[i] >= '0' && s[i] <= '9') {
                if (!k_dots) {
                    n1 = n1 * 10 + (s[i] - '0');
                } else {
                    n2 = n2 * 10 + (s[i] - '0');
                }
                k = 1;
            } else if(s[i] == '.' && !k_dots) {
                k_dots = 1;
            } else {
                *check_error_in_numbers = -2;
                break;
            }
        }
    }

    while (n2 >= 1.0) {
        n2 /= 10;
    }
    n1 = n1 + n2;

    if (minus) {
        n1 = -n1;
    }
    if (n1 == 0) {
        *check_error_in_numbers = -4;
    }
    if (k == 0) {
        *check_error_in_numbers = -3;
    }
    return n1;
}

int good_or_bad_number(char c, int* check_error_in_numbers) {
    if (*check_error_in_numbers == -3) {
        printf("No digits in the number!\n");
        *check_error_in_numbers = 1;
        return 0;
    } else if(*check_error_in_numbers == -1) {
        printf("Warning: number with '+' symbol\n");
        *check_error_in_numbers = 1;
        return 1;
    } else if(*check_error_in_numbers == -2) {
        printf("Mistake in writing the number! (character not a number)\n");
        *check_error_in_numbers = 1;
        return 0;
    } if (*check_error_in_numbers == -4) {
        if (c == 'm' || c == 't')
        { printf("Entered number 0! (err)\n"); return 0;}
        *check_error_in_numbers = 1;
        return 1;
    }
    return 1;
}

int entered_parameters_verify(int argc, char** argv) {
    if (argc <= 1) {
        printf("Parameters no entered!\n");
        return 0;
    }
    int i, k = 0;
    for (i = 0; argv[1][i] != '\0'; ++i) {
        k++;
    }
    if (k != 2) {
        printf("Flag entered incorrectly! (must be length 2)\n");
        return 0;
    }
    return 1;
} //в зависимости от чек ерор что-то печатает, и возвращается значение о продолжении работы программы. (если 0, то завершить)

double dicriminant(double a, double b, double c) {
    return (b * b - 4 * a * c);
}

void func_q(double a, double b, double c) {
    double d;
    printf("For the: (%.3lf) * x^2 + (%.3lf) * x + (%.3lf) = 0\n", a, b, c);
    if (a == 0) {
        printf("The number 'a' is not a parameter of the quadratic equation, because it should not be equal to 0\n\n");
    }
    else {
        d = dicriminant(a, b, c);
        if (d < 0) {
            printf("No roots.\n");
        } else if (d == 0) {
            printf("x = %lf\n", (-b + sqrt(d)) / (2 * a));
        } else {
            printf("x1 = %lf\n", (-b + sqrt(d)) / (2 * a));
            printf("x2 = %lf\n", (-b - sqrt(d)) / (2 * a));
        }
        printf("\n");
    }
}

int func_t(double a, double b, double c){
    if (a > 0 && b > 0 && c > 0)
        return (fabs(a * a + b * b - c * c) <= eps || fabs(c * c + b * b - a * a) <= eps || fabs(a * a + c * c - b * b) < eps);
    else
        return 0;
}

int main(int argc, char *argv[]) {
    int check_error_in_numbers = 1;

    double a = 0, b = 0, c = 0; // -q or -t
    int k1 = 0, k2 = 0; // -m

    int i;
    int good_flag = 0, ERRORS = 1;

    ERRORS = entered_parameters_verify(argc, argv); // проверка на длину флага и введены ли параметры вообще

    if (!(ERRORS)) {
        return 0;
    }


    char* parametrs [6] = {"-q", "/q", "-m", "/m", "-t", "/t"};
    for (i = 0; i < 6; i += 2) {
        if (!strcmp(parametrs[i], argv[1]) || !strcmp(parametrs[i + 1], argv[1])) {
            good_flag = 1;
            switch (parametrs[i][1]) {
                case 'q':
                    if (argc == 5) {
                        a = conv_to_double(argv[2], &check_error_in_numbers);
                        ERRORS = good_or_bad_number('q', &check_error_in_numbers);
                        if (!(ERRORS)) {
                            return 0;
                        }
                        b = conv_to_double(argv[3], &check_error_in_numbers);
                        ERRORS = good_or_bad_number('q', &check_error_in_numbers);
                        if (!(ERRORS)) {
                            return 0;
                        }
                        c = conv_to_double(argv[4], &check_error_in_numbers);
                        ERRORS = good_or_bad_number('q', &check_error_in_numbers);
                        if (!(ERRORS)) {
                            return 0;
                        }


                        func_q(a, b, c);
                        func_q(a, c, b);
                        func_q(b, a, c);
                        func_q(b, c, a);
                        func_q(c, a, b);
                        func_q(c, b, a);

                    } else {
                        printf("Need 3 arguments after the flag!\n");
                        return 0;
                    }
                    break;
                case 'm':
                    if (argc == 4) {
                        k1 = conv_n_to_int(argv[2], &check_error_in_numbers);
                        ERRORS = good_or_bad_number('m', &check_error_in_numbers);
                        if (!(ERRORS)) {
                            return 0;
                        }
                        k2 = conv_n_to_int(argv[3], &check_error_in_numbers);
                        ERRORS = good_or_bad_number('m', &check_error_in_numbers);
                        if (!(ERRORS)) {
                            return 0;
                        }

                        if (!(k1 == 0 || k2 == 0)) {
                            if (k1 % k2 == 0) {
                                printf("The first number is a multiple of the second!\n");
                            } else {
                                printf("The first number is not a multiple of the second!\n");
                            }
                        } else {
                            printf("One of the argument is 0!\n");
                            return 0;
                        }

                    } else {
                        printf("Need 2 arguments after the flag!\n");
                        return 0;
                    }
                    break;
                case 't':
                    if (argc == 5) {
                        a = conv_to_double(argv[2], &check_error_in_numbers);
                        ERRORS = good_or_bad_number('t', &check_error_in_numbers);
                        if (!(ERRORS)) {
                            return 0;
                        }
                        b = conv_to_double(argv[3], &check_error_in_numbers);
                        ERRORS = good_or_bad_number('t', &check_error_in_numbers);
                        if (!(ERRORS)) {
                            return 0;
                        }
                        c = conv_to_double(argv[4], &check_error_in_numbers);
                        ERRORS = good_or_bad_number('t', &check_error_in_numbers);
                        if (!(ERRORS)) {
                            return 0;
                        }

                        if (func_t(a, b, c)) {
                            printf("Yes, the entered values can be the sides of a right triangle.\n");
                        } else {
                            printf("No, the entered values cannot be the sides of a right triangle.\n");
                        }

                    } else {
                        printf("Need 3 arguments after the flag!\n");
                        return 0;
                    }
                    break;
            }
        }
    }
    if(!good_flag) {
        printf("Invalid flag entered! (Flag start in '-' or '/' and then one of the 'qmt')\n");
    }

    return 0;
}
