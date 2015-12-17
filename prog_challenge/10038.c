#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int num[3000];
int exist[3000];

void jollyJumper(int n)
{
    int i, t;

    for (i = 0; i < n-1; i++) {
        t = abs(num[i]-num[i+1]);
        if (t == 0 || t >= n || exist[t]) {
            printf("Not jolly\n");
            return ;
        }
        exist[t] = 1;
    }
    if (i == 0 && num[i] != 1)
        printf("Not jolly\n");
    else
        printf("Jolly\n");
}

int main(int argc, char* argv[])
{
    int n;
    int i;

    while (1) {
        memset(exist, 0, sizeof(exist));
        if(scanf("%d", &n) == EOF)
            break;

        for (i = 0; i < n; i++) {
            scanf("%d", &num[i]);
        }

        jollyJumper(n);
    }

    return 0;
}
