#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>

#define min(X, Y) (((X) < (Y)) ? (X) : (Y))

#define max(X, Y) (((X) > (Y)) ? (X) : (Y))

void swap(char* s, int left, int right) {
    char tmp = s[left];
    s[left] = s[right];
    s[right] = tmp;
}

int length(const char *str) {
    int i = 0;
    while (str[++i]);
    return i;
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


void reverse(char* str) {
    int n = length(str);
    for(int i = 0; i < n / 2; ++i)
        swap(str, i, n - 1 - i);
}

char* sum_in_cc(char* str1, char* str2, int n) {
    int len1 = length(str1);
    int len2 = length(str2);
    int len_result = max(len1, len2) + 2;
    char* result = (char*)malloc(sizeof(char) * len_result);
    for (int i = 0; i < len_result - 1; ++i) result[i] = '0';
    result[len_result - 1] = '\0';

    int pointers [] = {len1 - 1, len2 - 1};

    int s = 0;

    for(int i = len_result - 2; i >= 0; --i) {
        result[i] = ((pointers[0] >= 0) ? (to_integer(str1[pointers[0]])) : 0) + ((pointers[1] >= 0) ? (to_integer(str2[pointers[1]])) : 0) + s;
        s = result[i] / n;
        result[i] = to_char(result[i] % n);
        --pointers[0];
        --pointers[1];
    }

    return result;
}



int main(int argc, char *argv[]) {

    int n = 16;
    char str1 [] = "0FFF";
    char str2 [] = "FFFF";
    char* str3 = sum_in_cc(str1, str2, n);

    printf("%s", str3);
    free(str3);

    return 0;
}