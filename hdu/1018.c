#include <math.h>
#include <stdio.h>
#include <stdlib.h>


// Another Method: Striling number, equation

// Method #1:
int main(int argc, char** argv) {
    int num, n, res, i;
    double temp;

    scanf("%d", &num);

    while (num-- > 0) {
        scanf("%d", &n);
        
        temp = 0.0f;
        for (i = 1; i <= n; i++) {
            temp += log10(i);
        }

        res = (int)temp + 1;

        printf("%d\n", res);
    }

    return 0;
}
