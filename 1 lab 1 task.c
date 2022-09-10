#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*
int str_len(char* s){
    int n;
    for(n = 0; s[n] != '\0'; n++){}
    return n;
}*/

long long conv_n_to_int(char* s){
    int i;
    long long n = 0;
    for (int i = 0; i < s[i] != '\0'; i++) {
        if(s[i] != '\0') {
            n = n * 10 + (s[i] - '0');
        }
    }
    return n;
}

void func_h(long long n){
    int i = 0, k = 0;

    for (int i = 0; i <= 100 ; ++i) {
        if (i % n == 0) {
            printf("%d ", i);
            k++;
        }
    }
    if(k){
        printf("- mulpiples of %lld", n);
    } else {
        printf("Within 100 there are no multiples of the entered %lld", n);
    }
    printf("\n");
}

void func_p(long long n){
    long long i;
    int k = 0;
    for (i = 2; i <= sqrt(n); i++) {
        if(n % i == 0) {
            k = 1;
            break;
        }
    }
    if(k){
        printf("The number %lld is composite!\n", n);
    } else{
        printf("The number %lld is prime!\n", n);
    }
}

void func_s(char* s){
    int i;
    for(i = 0; s[i] != '\0'; i++)
    {
        printf("%c ", s[i]);
    }
    printf("\n");
}

long long power(int a, long long b){
    long long p = 1;
    for (int i = 0; i < b; i++) {
        p *= a;
    }
    return p;
}

void func_e(long long n){
    if(n <= 10) {
        int i, j;
        for (i = 1; i <= 10; i++) {
            printf("%d - ", i);
            for (j = 1; j <= n; j++) {
                printf("%lld ", power(i, j));
            }
            printf("\n");
        }
    } else {
        printf("A number greater than 10 has been entered!\n");
    }
}

void func_a(long long n){
    printf("%lld\n", n * (n + 1) / 2);
}

long long factorial(long long n){
    if (n > 1) return n * factorial(n - 1);
    else return 1;
}

void func_f(long long n){
    if (n <= 20) {
        printf("The factorial of %lld is %lld", n, factorial(n));
    } else {
        printf("The number %lld is too big!", n);
    }
}

void main(int argc, char *argv[]) {

    int i, j;
    int n = conv_n_to_int(argv[1]);
    char parametrs [12][3] = {"-h", "/h", "-p", "/p", "-s", "/s", "-e", "/e", "-a", "/a", "-f", "/f"};


    for (int i = 0; i < 12; i += 2) {
        if (strcmp(parametrs[i], argv[2]) == 0 || strcmp(parametrs[i + 1], argv[2]) == 0) {
            switch (parametrs[i][1]) {
                case 'h':
                    func_h(n);
                    break;
                case 'p':
                    func_p(n);
                    break;
                case 's':
                    func_s(argv[1]);
                    break;
                case 'e':
                    func_e(n);
                    break;
                case 'a':
                    func_a(n);
                    break;
                case 'f':
                    func_f(n);
                    break;
                default:
                    printf("Invalid flag entered!\n");
                    break;
            }
        }
    }
}
