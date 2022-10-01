#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
//#include <math.h>
//#include <limits.h>
//#include <ctype.h>
//#define min(X, Y) (((X) < (Y)) ? (X) : (Y))

#define max(X, Y) (((X) > (Y)) ? (X) : (Y))

void swap(char* s, int left, int right) {
    char tmp = s[left];
    s[left] = s[right];
    s[right] = tmp;
}

int to_integer(char c)
{
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    else if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    else if (c >= '0' && c <= '9') return c - '0';
    else return -1;
}

int to_char(char c)
{
    if (c >= 10 && c <= 26) return c + 'A' - 10;
    else if (c >= 0 && c <= 9) return c + '0';
    else return -1;
}

char* sum_in_cc(char* str1, char* str2, int n) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len_result = max(len1, len2) + 1;
    char* result = (char*)malloc(sizeof(char) * len_result);
    for (int i = 0; i < len_result - 1; ++i) result[i] = '0';
    result[len_result] = '\0';

    int pointers [] = {len1 - 1, len2 - 1};

    int s = 0;

    for(int i = len_result - 1; i >= 0; --i) {
        result[i] = ((pointers[0] >= 0) ? (to_integer(str1[pointers[0]])) : 0) + ((pointers[1] >= 0) ? (to_integer(str2[pointers[1]])) : 0) + s;
        s = result[i] / n;
        result[i] = to_char(result[i] % n);
        --pointers[0];
        --pointers[1];
    }

    int i = 0, k_0 = 0, l = 0;
    while (result[i] == '0') {++k_0; ++i;}

    char* result_without_starting_0 = (char*)malloc(sizeof(char*) * (len_result - k_0));
    for(int j = i; j <= len_result; ++j) {
        result_without_starting_0[l] = result[j];
        ++l;
    }
    //printf("%d %d\n", k_0, len_result);
    free(result);

    return result_without_starting_0;
}

char* sum_arguments(int n, ...)
{
    char* result = "";
    va_list factor;
    va_start(factor, n);
    int system_of_counting = va_arg(factor, int);
    for(int i = 1; i < n; i++)
    {
        result = sum_in_cc(result, va_arg(factor, char*), system_of_counting);
    }
    va_end(factor);
    return result;
}


int main(int argc, char *argv[]) {

    int system_of_counting = 16, n_arguments = 4;
    char* str1 = "FF";
    char* str2 = "FF";
    char* str3 = "0FFFF";
    char* res = sum_arguments(n_arguments, system_of_counting, str1, str2, str3);
    printf("%s", res);
    free(res);

    return 0;
}
