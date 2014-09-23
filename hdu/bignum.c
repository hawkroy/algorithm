#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add_bignum(char ** psum, char * a, char * b) {
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    size_t len = ((len_a > len_b)? len_a: len_b)+1;
    char * sum;
    unsigned char temp;

    sum = (char *)malloc(len);
    if (sum == NULL) {
        return MALLOC_ERROR;
    }

    memset(sum, 0, len);

    for (int i = 1; (i < len_a) && (i < len_b); i++) {
        temp = (sum[i]-'0')+(a[i]-'0')+(b[i]-'0');
        sum[i] = temp % 10+'0';
        sum[i+1] = temp / 10+'0';
    }

    if (len_a < len_b) {
    }
    else {
    }

    sum[0] = '\0';

    (*psum) = sum;
    return OK;
}

int mul_bignum(char ** pprod, char * a , char * b) {
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    size_t len = len_a+len_b+1;
    char * prod;
    unsigned int temp;

    prod = (char *)malloc(len);
    if (prod == NULL) {
        return MALLOC_ERROR;
    }

    memset(prod, 0, len);

    for (int i = 1; i < len; i++) {
        temp = prod[i]
    }

    (*pprod) = prod;
    return OK;
}
