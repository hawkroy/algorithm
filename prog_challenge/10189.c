#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[100];
int result[102][102];

void update(int i, int j)
{
    int ii, jj;
    for (ii = i-1; ii < i+2; ii++)
        for (jj = j-1; jj < j+2; jj++)
            if (result[ii][jj] != -1)
                result[ii][jj]++;
    return ;
}

int main(int argc, char* argv[])
{
    int m, n;
    int i, j;
    int cnt = 1;

    while (scanf("%d %d", &n, &m) != EOF) {
        memset(result, 0, sizeof(result));
        if (m == 0 && n == 0)
            break;

        i = 0;
        while (i < n) {
            scanf("%s", input);

            for (j = 0; j < m; j++) {
                if (input[j] == '*')
                    result[i+1][j+1] = -1;
            }
            i++;
        }

        for (i = 0; i < n; i++)
            for (j = 0; j < m; j++)
                if (result[i+1][j+1] == -1)
                    update(i+1, j+1);

        if (cnt > 1)
            printf("\n");
        printf("Field #%d:\n", cnt++);
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                if (result[i+1][j+1] == -1)
                    printf("*");
                else
                    printf("%d", result[i+1][j+1]);
            }
            printf("\n");
        }
    }

    return 0;
}
