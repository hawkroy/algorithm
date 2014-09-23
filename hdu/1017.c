#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char **argv) {
    int num;
    int cnt, solution;
    int n, m, a, b;

    scanf("%d", &num);

    while (num-- > 0) {
        cnt = 0;

        while (1) {
            scanf("%d %d", &n, &m);

            if (!(n || m))
                break;
            
            solution = 0;
            cnt++;
            for(a = 1; a < n; a++) {
                for (b = a + 1; b < n; b++) {
                    if ((a*a+b*b+m) % (a*b) == 0) {
                        solution++;
                    }
                }
            }    
            printf("Case %d: %d\n", cnt, solution);
        }
        if (num != 0)
            printf("\n");

    }
    return 0;
}
