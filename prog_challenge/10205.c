#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int deck[2][52];
int shuffle[100][52];

char *value[] =
{
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
    "Jack",
    "Queen",
    "King",
    "Ace",
};

char *suit[] =
{
    "Clubs",
    "Diamonds",
    "Hearts",
    "Spades",
};

int main(int argc, char *argv[])
{
    int *cur, *mirror, *temp;
    int cases, n , i, j;
    char line[100];

    cur = deck[0];
    mirror = deck[1];
    scanf("%d", &cases);
    while (cases-- > 0) {
        for (i = 0; i < 52; i++)
            cur[i] = i;

        scanf("%d", &n);
        for (i = 0; i < n; i++)
            for (j = 0; j < 52; j++)
                scanf("%d", &shuffle[i][j]);
        fgets(line, sizeof(line), stdin);

        while (fgets(line, sizeof(line), stdin) != NULL) {
            if (line[0] == '\r' || line[0] == '\n')
                break;
            sscanf(line, "%d", &i);
            i--;

            for (j = 0; j < 52; j++)
                mirror[j] = cur[shuffle[i][j]-1];

            temp = cur;
            cur = mirror;
            mirror = temp;
        }

        for (i = 0; i < 52; i++)
            printf("%s of %s\n", value[cur[i]%13], suit[cur[i]/13]);

        if (cases != 0)
            printf("\n");
    }

    return 0;
}
