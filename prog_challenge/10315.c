#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int black[13];
int black_type;
char black_cmp[5];
int white[13];
int white_type;
char white_cmp[5];

int transType(int type, int i, int t)
{
    static int start_i = 0;
    static int num = 0;

    if (type == 0 && t == 1 && num == 0)
        start_i = i;

    num += t;
    switch (type) {
    case 0:
        /*HIGH*/
        if (t == 1) {
            if ((num == 5) && (i-start_i+1 == num))
                type = 4;
        }
        else if (t == 2) {
            type = 1;
        }
        else if (t == 3) {
            type = 3;
        }
        else if (t == 4) {
            type = 7;
        }
        break;
    case 1:
        /*PAIR*/
        if (t == 2) {
            type = 2;
        }
        else if (t == 3) {
            type = 6;
        }
        break;
    case 2:
        /*TWO PAIR*/
        break;
    case 3:
        /*THREE*/
        if (t == 2) {
            type = 6;
        }
        break;
    case 4:
        /*STRAIGHT*/
        break;
    case 5:
        /*FLUSH*/
        break;
    case 6:
        /*HORSE*/
        break;
    case 7:
        /*FOUR*/
        break;
    case 8:
        /*STRAIGHT FLUSH*/
        break;
    }

    if (num == 5)
        num = 0;

    return type;
}

int commonSuit(int* suits, char* str, char* cmp)
{
    int i, j, max = 0, max_num = 1;
    char t, c, orig_c = '\0';
    int same_suit = 1;
    int type = 0;
    char* cur = &cmp[4];

    for (i = 0; i < 15; i += 3) {
        sscanf(str+i, "%c%c", &t, &c);
        if (orig_c != '\0' && c != orig_c)
            same_suit = 0;
        orig_c = c;
        if (t == 'T')
            t = 8;
        else if (t == 'J')
            t = 9;
        else if (t == 'Q')
            t = 10;
        else if (t == 'K')
            t = 11;
        else if (t == 'A')
            t = 12;
        else
            t = t-'0'-2;
        suits[t]++;
    }

    for (i = 0; i < 13; i++)
        type = transType(type, i, suits[i]);

    if (same_suit && type == 4)
        type = 8;
    else if (same_suit && type <4)
        type = 5;

    for (i = 0; i < 13; i++) {
        if (suits[i] != 0) {
            if (suits[i] < max && type != 5) {
                cur -= suits[i];
                /* 
		 * for memcpy&strcpy, the source and dest can't overlap
		 */
                memmove(cur+1, cur+suits[i]+1, max*max_num);
                for (j = 0; j < suits[i]; j++)
                    *(cur+1+max*max_num+j) = i;
            }
            else {
                if (max == suits[i])
                    max_num++;
                else {
                    max = suits[i];
                    max_num = 1;
                }
                for (j = 0; j < suits[i]; j++)
                    *(cur--) = i;
            }
        }
    }

    return type;
}

void blackSuit(char *str)
{
#ifndef ONLINE_JUDGE
    int i;
#endif

    black_type = commonSuit(black, str, black_cmp);

#ifndef ONLINE_JUDGE
    printf("black_type=%d\n", black_type);

    for (i = 0; i < 13; i++)
        printf("black_suit[%d]=%d ", i, black[i]);
    printf("\n");

    for (i = 0; i < 5; i++)
        printf("black_cmp[%d]=%d ", i, black_cmp[i]);
    printf("\n");
#endif
}

void whiteSuit(char* str)
{
#ifndef ONLINE_JUDGE
    int i;
#endif

    white_type = commonSuit(white, str, white_cmp);

#ifndef ONLINE_JUDGE
    printf("white_type=%d\n", white_type);

    for (i = 0; i < 13; i++)
        printf("white_suit[%d]=%d ", i, white[i]);
    printf("\n");

    for (i = 0; i < 5; i++)
        printf("white_cmp[%d]=%d ", i, white_cmp[i]);
    printf("\n");
#endif
}

void whoWin()
{
    int t;

    if (black_type > white_type)
        printf("Black wins.\n");
    else if (white_type > black_type)
        printf("White wins.\n");
    else {
        t = memcmp(black_cmp, white_cmp, 5);
        if (t > 0) {
            printf("Black wins.\n");
            return ;
        }
        else if (t < 0) {
            printf("White wins.\n");
            return ;
        }
        else {
            printf("Tie.\n");
        }
    }
    return ;
}

int main(int argc, char* argv[])
{
    char line[100];

    while (fgets(line, sizeof(line), stdin) != NULL) {
        memset(black, 0, sizeof(black));
        memset(white, 0, sizeof(white));
        blackSuit(line);
        whiteSuit(line+15);
        whoWin();
    }

    return 0;
}
