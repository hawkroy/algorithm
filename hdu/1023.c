#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

// Catalan number: h(n) = h(0)h(n-1)+h(1)h(n-2)+....+h(n-2)h(1)+h(n-1)h(0),[n>=2], h(0)=h(1)=1
//      h(n) = h(n-1)*(4n-2)/(n+1)
//      h(n) = c(2n,n)/(n+1) = c(2n,n)-c(2n,n+1)
//      h(n) ~ 4^n/(n^(3/2)*sqrt(pi)) ~ O(4^n)


// big number multiply & divide
#define MAX 1000

int catalan[MAX];

char * calcCatalan(int n) {
    int i = 0;
    
    for (i = 0; i < MAX; i++) {
    
        // multiply
        for (j = 0; j < MAX; j++) {
            catlan[i][j] = catlan[i-1][j]*(4*i-2);
        }
        
        // carrry handle
        
        // divide
    }
    
    return ;
}

int main(int argc, char** argv) {
    int n;
    char * res  = NULL;

    while (scanf("%d", &n) != EOF) {
        memset(catalan, NULL, MAX);
        res = calcCatalan(n);
        printf("%s\n", res);
    }

    return 0;
}
