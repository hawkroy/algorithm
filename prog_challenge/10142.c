#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char candidate[20][90];
int count[20];
int vote[1000][20];
int election_cnt;
int candidate_cnt;

void election()
{
    int remove = 0;
    int winner = -1;
    int min;
    int i, j;
    int turn = 0;

    memset(count, 0, sizeof(count));
    /*
     * maybe more optimization
     */
    while (winner == -1 && remove < candidate_cnt) {
        turn++;
        min = election_cnt+1;

        for (i = 0; i < candidate_cnt; i++)
            if (count[i] >= 0)
                count[i] = 0;

        for (i = 0; i < election_cnt; i++) {
            j = 0;
            while (j < candidate_cnt && count[vote[i][j]-1] < 0)
                j++;
            if (j < candidate_cnt)
                count[vote[i][j]-1]++;
        }

        for (i = 0; i < candidate_cnt; i++) {
            if (count[i] > election_cnt/2) {
                winner = i;
                break;
            }
            if (count[i] >= 0 && count[i] < min) {
                min = count[i];
            }
        }

        for (i = 0; i < candidate_cnt; i++)
            if (count[i] == min) {
                count[i] = 0-turn;
                remove++;
            }
    }

    if (winner != -1)
        printf("%s", candidate[winner]);
    if (remove == candidate_cnt) {
        for (i = 0; i < candidate_cnt; i++)
            if (count[i] == 0-turn)
                printf("%s", candidate[i]);
    }
}

int main(int argc, char* argv[])
{
    int cases;
    char line[100];
    char* p;
    int i, j, n;

    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &cases);
    fgets(line, sizeof(line), stdin);

    while (cases-- > 0) {
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%d", &n);
        candidate_cnt = n;

        i = 0;
        while (n-- > 0) {
            fgets(line, sizeof(line), stdin);
            strncpy(candidate[i], line, strlen(line));
            candidate[i][strlen(line)] = '\0';
            i++;
        }

        i = 0;
        while (fgets(line, sizeof(line), stdin) != NULL) {
            if (line[0] == '\r' || line[0] == '\n')
                break;

            /*
             * we should be care of the input handle
             */
            p = line;
            for (j = 0; j < candidate_cnt; j++) {
                sscanf(p, "%d", &vote[i][j]);
                p++;
                p = strchr(p, ' ');
            }
            i++;
        }
        election_cnt = i;

        election();

        if (cases != 0)
            printf("\n");
    }

    return 0;
}
