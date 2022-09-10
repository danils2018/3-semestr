#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

long long conv_n_to_int(char* s, int* check_error_in_n){
    int i, minus = 0, k = 0;
    long long n = 0;

    for (i = 0; s[i] != '\0'; i++) {
        if (i == 0) {
            if (s[i] == '-') {
                minus = 1;
            } else if (s[i] == '+') {
                *check_error_in_n = -1;
            } else if (s[i] >= '0' && s[i] <= '9') {
                n = n * 10 + (s[i] - '0');
                k = 1;
            } else {
                *check_error_in_n = -2;
                break;
            }
        } else {
            if (s[i] >= '0' && s[i] <= '9') {
                n = n * 10 + (s[i] - '0');
                k = 1;
            } else {
                *check_error_in_n = -2;
                break;
            }
        }


    }
    if (k == 0){
        *check_error_in_n = -3;
    }
    if (minus) {
        n = -n;
    }
    if (n <= 0) {
        *check_error_in_n = -4;
    }

    return n;
} //Здесь коды ошибок кладутся в чек ерор и одновременно с этим переводится число из строки в ll

int Prime(long long n){
    if (n < 2) return 0;
    long long i;
    int k = 1;
    for (i = 2; i <= floor(sqrt(n)); i++) {
        if(n % i == 0) {
            k = 0;
            break;
        }
    }
    return k;
} // Проверка на простоту (1, если простое)

long long factorial(long long n){
    if (n > 1) {
        if (LLONG_MAX / n > factorial(n - 1))
        {
            return n * factorial(n - 1);
        } else {
            return -1;
        }
    }
    else return 1;
} //Факториал

int entered_parameters_verify(long long n, int argc, char* argv, int check_error_in_n) {
    if (argc != 3) {
        printf("Invalid input format! (Need 3 arguments)\n");
        return 0;
    } else if(check_error_in_n == -4) {
        printf("Entered non-positive number!\n");
        return 0;
    } else if(check_error_in_n == -3) {
        printf("No digits in the number!\n");
        return 0;
    } else if(check_error_in_n == -2) {
        printf("Mistake in writing the number n! (character not a number)\n");
        return 0;
    } else if(check_error_in_n == -1) {
        printf("Warning: number with '+' symbol\n");
        return 1;
    }
    int i, k = 0;
    for (i = 0; argv[i] != '\0'; i++) {
        k ++;
    }
    if (k != 2) {
        printf("Flag entered incorrectly! (must be length 2)\n");
        return 0;
    }
    return 1;
} //в зависимости от чек ерор что-то печатает, и возвращается значение о продолжении работы программы. (если 0, то завершить)

int main(int argc, char *argv[]) {
    int check_error_in_n = 1;
    long long power_func_e;
    int i, l, i1, j1, x, ih, kh, good_flag = 0, ERRORS = 1;
    long long n;
    if (argc > 1) {
        n = conv_n_to_int(argv[1], &check_error_in_n);
        //printf("%d\n", check_error_in_n);
        ERRORS = entered_parameters_verify(n, argc, argv[2], check_error_in_n);
    } else {
        printf("Parameters no entered!\n");
        return 0;
    }
    if (ERRORS == 0) {
        return 0;
    }
    char parametrs [12][3] = {"-h", "/h", "-p", "/p", "-s", "/s", "-e", "/e", "-a", "/a", "-f", "/f"};


    for (i = 0; i < 12; i += 2) {
        if (strcmp(parametrs[i], argv[2]) == 0 || strcmp(parametrs[i + 1], argv[2]) == 0) {
            good_flag = 1;
            switch (parametrs[i][1]) {
                case 'h':
                    kh = 0;
                    for (ih = 0; ih <= 100 ; ++ih) {
                        if (ih % n == 0) {
                            printf("%d ", ih);
                            kh++;
                        }
                    }
                    if(kh){
                        printf("- mulpiples of the entered %lld", n);
                    } else {
                        printf("Within 100 there are no multiples of the entered %lld", n);
                    }
                    printf("\n");
                    break;
                case 'p':
                    x = Prime(n);
                    if(x) {
                        printf("The number %lld is prime!\n", n);
                    } else{
                        printf("The number %lld is not prime!\n", n);
                    }
                    break;
                case 's':
                    for(l = 0; argv[1][l] != '\0'; l++)
                    {
                        printf("%c ", argv[1][l]);
                    }
                    printf("\n");
                    break;
                case 'e':
                    if(n <= 10) {
                        for (i1 = 1; i1 <= 10; i1++) {
                            printf("%d - ", i1);
                            power_func_e = i1;
                            for (j1 = 1; j1 <= n; j1++) {
                                printf("%lld ", power_func_e);
                                power_func_e *= i1;
                            }
                            printf("\n");
                        }
                    } else {
                        printf("A number greater than 10 has been entered!\n");
                    }
                    break;
                case 'a':
                    printf("Sum from 1 to %lld inclusive: %lld\n", n, n * (n + 1) / 2);
                    break;
                case 'f':
                    if (factorial(n) != -1) {
                        printf("The factorial of %lld is %lld", n, factorial(n));
                    } else {
                        printf("The number %lld is too big!", n);
                    }
                    break;
            }
        }
    }
    if(!good_flag) {
        printf("Invalid flag entered! (Flag start in '-' or '/' and then one of the 'hpseaf')\n");
    }
    return 0;
}