#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TesterInfo
{
    unsigned int solve;
    unsigned int total;
    int index;
    int valid;
    int try[9];
} g_testers[100];

int cmp(const void *cmp1, const void *cmp2)
{
    const struct TesterInfo* test1 = (const struct TesterInfo*)cmp1;
    const struct TesterInfo* test2 = (const struct TesterInfo*)cmp2;

    if (test1->solve > test2->solve)
        return -1;
    else if (test1->solve < test2->solve)
        return 1;
    else if (test1->total > test2->total)
        return 1;
    else if (test1->total < test2->total)
        return -1;
    else if (test1->valid > test2->valid)
        return -1;
    else if (test1->valid < test2->valid)
        return 1;
    else if (test1->index < test2->index)
        return -1;
    else
        return 0;
}

int main(int argc, char *argv[])
{
    char line[100];
    int cases, i;
    unsigned int test, problem, time;
    char status;

    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &cases);
    fgets(line, sizeof(line), stdin);

    while (cases-- > 0) {
        memset(g_testers, 0, sizeof(g_testers));

        while (fgets(line, sizeof(line), stdin) != NULL) {
            if (line[0] == '\r' || line[0] == '\n')
                break;

            sscanf(line, "%d %d %d %c", &test, &problem, &time, &status);

            if (status == 'C' && g_testers[test-1].try[problem-1] >= 0) {
                g_testers[test-1].solve++;
                g_testers[test-1].total += time;
                g_testers[test-1].total += g_testers[test-1].try[problem-1]*20;
                g_testers[test-1].try[problem-1] = -1;
            }
            else if (status == 'I' && g_testers[test-1].try[problem-1] >= 0) {
                g_testers[test-1].try[problem-1]++;
            }
            g_testers[test-1].index = test;
            g_testers[test-1].valid = 1;
        }

        qsort(g_testers, 100, sizeof(struct TesterInfo), cmp);

        for (i = 0; i < 100 && g_testers[i].valid != 0; i++)
            printf("%d %d %d\n", g_testers[i].index, g_testers[i].solve, g_testers[i].total);

        if (cases != 0)
            printf("\n");
    }

    return 0;
}
