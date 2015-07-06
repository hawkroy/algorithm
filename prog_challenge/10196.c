#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char chessboard[8][8];

struct dir{
    int i;
    int j;
    char* str;
    int once;
} direction[] =
{
    {0, -1, "rq", 0},
    {-1, -1, "bq", 0},
    {-1, 0, "rq", 0},
    {-1, 1, "bq", 0},
    {0, 1, "rq", 0},
    {1, 1, "bq", 0},
    {1, 0, "rq", 0},
    {1, -1, "bq", 0},
    {-1, -2, "n", 1},
    {-2, -1, "n", 1},
    {-2, 1, "n", 1},
    {-1, 2, "n", 1},
    {1, 2, "n", 1},
    {2, 1, "n", 1},
    {2, -1, "n", 1},
    {1, -2, "n", 1},
};

int checkTheCheck(char king)
{
    int i, j, d, s;
    int k_i, k_j;
    int white = 0;
    char c;

    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            if (chessboard[i][j] == king)
                goto done;
    return -1;
done:
    k_i = i, k_j = j;

    if (king == 'K')
        white = 1;

    if (white) {
        if (k_i > 0 && k_j > 0 && chessboard[k_i-1][k_j-1] == 'p')
            return 1;
        if (k_i > 0 && k_j < 7 && chessboard[k_i-1][k_j+1] == 'p')
            return 1;
    }
    else {
        if (k_i < 7 && k_j > 0 && chessboard[k_i+1][k_j-1] == 'P')
            return 1;
        if (k_i < 7 && k_j < 7 && chessboard[k_i+1][k_j+1] == 'P')
            return 1;
    }

    /*
     * NOTE: when impl, should consider over-flow issue
     */
    for (d = 0; d < sizeof(direction)/sizeof(struct dir); d++) {
        i = k_i, j = k_j;

        do {
            i += direction[d].i;
            j += direction[d].j;

            if (!(i >= 0 && i < 8 && j >= 0 && j < 8))
                break;

            for (s = 0; s < strlen(direction[d].str); s++) {
                if (white)
                    c = direction[d].str[s];
                else
                    c = direction[d].str[s]-32;

                if (chessboard[i][j] == c)
                    return 1;
            }
        } while (chessboard[i][j] == '.' && !direction[d].once);
    }

    return 0;
}

int main(int argc, char* argv[])
{
    char line[20];
    int cases = 0;
    int i, ret;

    while (1) {
        cases++;
        for (i = 0; i < 8; i++)
            scanf("%s", chessboard[i]);

        fgets(line, sizeof(line), stdin);

        ret = checkTheCheck('k');
        if (ret == 1) {
            printf("Game #%d: black king is in check.\n", cases);
            continue;
        }

        ret = checkTheCheck('K');
        if (ret == 1) {
            printf("Game #%d: white king is in check.\n", cases);
            continue;
        }

        if (ret == -1)
            break;

        printf("Game #%d: no king is in check.\n", cases);
    }

    return 0;
}
