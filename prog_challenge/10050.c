#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parties[100];
int days[3651];
int total_days;

void solve(int n)
{
    int i, j;
    int lose = 0;

    for (i = 0; i < n; i++) {
        j = parties[i];

        while (j <= total_days) {
            if (days[j] == 0 && !(j%7==6 || j%7==0)) {
                lose++;
                days[j] = 1;
            }
            j += parties[i];
        }
    }

    printf("%d\n", lose);

    return;
}

int main(int argc, char* argv[])
{
    int cases;
    int n, i;

    scanf("%d", &cases);

    while (cases-- > 0) {
        memset(days, 0, sizeof(days));

        scanf("%d", &total_days);

        scanf("%d", &n);
        for (i = 0; i < n; i++) {
            scanf("%d", &parties[i]);
        }

#ifndef ONLINE_JUDGE
        printf("total_days=%d\n", total_days);
        printf("parties=%d\n", n);
        for (i = 0; i < n; i++) {
            printf("party[%d]=%d ", i, parties[i]);
        }
        printf("\n");
#endif

        solve(n);
    }

    return 0;
}
