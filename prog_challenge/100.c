#include <stdio.h>
#include <stdlib.h>

int solve(int i, int j)
{
    int max = 0;
    int cnt;
    long long k;

    if (i > j) {
        k = i;
        i = j;
        j = k;
    }

    while (i <= j) {
        cnt = 1;
        k = i;
        while (k != 1) {
            cnt++;
            if (k%2 == 0)
                k /= 2;
            else
                k = k*3+1;
        }
        if (cnt > max)
            max = cnt;
        i++;
    }
    return max;
}

int main(int argc, char* argv[])
{
    int i, j;
    while (scanf("%d %d", &i, &j) != EOF) {
        printf("%d %d %d\n", i, j, solve(i, j));
    }
    return 0;
}
