/*
 * Note: need more check or modify
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DictElement {
    char word[20];
    char feature[20];
    struct DictElement* next;
} dict[1000];
struct DictElement* size_map[16];

int alpha_map[26];
int alpha_bits;

int buildFeature(char *word, char *feature)
{
    int i, cnt, sum;
    char c;

    i = 1, cnt = 1, sum = 0;
    c = word[0];

    do {
        if (c == word[i])
            cnt++;
        else {
            feature += sprintf(feature, "%d", cnt);
            c = word[i];
            sum += cnt;
            cnt = 1;
        }
    } while (word[i++] != '\0');
    *feature = '\0';

    return sum;
}

void preHandleDict(int n)
{
    int i, cnt;

    for (i = 0; i < n; i++) {
        cnt = buildFeature(dict[i].word, dict[i].feature);

        dict[i].next = size_map[cnt-1];
        size_map[cnt-1] = &dict[i];
    }

#ifndef ONLINE_JUDGE
    for (i = 0; i < n; i++) {
        printf("dict[%d]: word=%s, feature=%s\n", i, dict[i].word, dict[i].feature);
    }
#endif

    return ;
}

int decrypt(char *line)
{
    char *p;
    char feature[20];
    struct DictElement* p_dict_element;
    int cnt, i, j, found, ret;
    int bits;

    p = strchr(line, ' ');
    if (p != NULL)
        *p = '\0';

    cnt = buildFeature(line, feature);
#ifndef ONLINE_JUDGE
    printf("cur word=%s, feature=%s\n", line, feature);
#endif
    if (p != NULL)
        *p = ' ';

    for (p_dict_element = size_map[cnt-1]; p_dict_element != NULL; p_dict_element = p_dict_element->next) {
        bits = alpha_bits;
        found = 0;
        if (strcmp(p_dict_element->feature, feature) == 0) {
            found = 1;
            for (j = 0, i = 0; i < strlen(feature); j+=(feature[i]-'0'), i++) {
                if (alpha_map[line[j]-'a'] == 0 && !(bits & 1<<(p_dict_element->word[j]-'a'))) {
                    bits |= 1<<(p_dict_element->word[j]-'a');
                    alpha_map[line[j]-'a'] = p_dict_element->word[j];
                }
                else if (alpha_map[line[j]-'a'] != p_dict_element->word[j]) {
                    found = 0;
                    break;
                }
            }
        }

        bits ^= alpha_bits;
        if (!found) {
            for (j = 0, i = 0; i < strlen(feature); j+=(feature[i]-'0'), i++) {
                if (bits & 1<<(p_dict_element->word[j]-'a')) {
                    bits &= ~(1<<(p_dict_element->word[j]-'a'));
                    alpha_map[line[j]-'a'] = 0;
                }
            }
            continue;
        }
        alpha_bits |= bits;

#ifndef ONLINE_JUDGE
        for (j = 0, i = 0; i < strlen(feature); j+=(feature[i]-'0'), i++)
            if (alpha_map[line[j]-'a'] != 0)
                printf("map %c to %c, ", line[j], alpha_map[line[j]-'a']);
        printf("\n");
#endif

        if (p == NULL)
            return 1;

        ret = decrypt(p+1);
        if (ret != 0)
            return ret;

        alpha_bits ^= bits;
        for (j = 0, i = 0; i < strlen(feature); j+=(feature[i]-'0'), i++) {
            if (bits & 1<<(p_dict_element->word[j]-'a'))
                alpha_map[line[j]-'a'] = 0;
        }
    }

    if (size_map[cnt-1] == NULL)
        return 2;

    return 0;
}

int main(int argc, char *argv[])
{
    int n, i;
    char line[100];
    char work_line[100];
    char *p;
    int ret;

    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &n);

    i = 0;
    while (fgets(line, sizeof(line), stdin) != NULL) {
        p = strchr(line, '\n');
        if (*(p-1) == '\r')
            *(p-1) = '\0';
        else
            *p = '\0';
        strncpy(dict[i].word, line, strlen(line));
        dict[i].word[strlen(line)] = '\0';
        if ((++i) == n)
            break;
    }
    preHandleDict(n);

    while (fgets(line, sizeof(line), stdin) != NULL) {
        memset(alpha_map, 0, sizeof(alpha_map));
        alpha_bits = 0;
        p = strchr(line, '\n');
        if (*(p-1) == '\r')
            *(p-1) = '\0';
        else
            *p = '\0';
        ret = decrypt(line);
#ifndef ONLINE_JUDGE
        printf("ret=%d\n", ret);
#endif
        if (ret == 1) {
            for (i = 0; i < strlen(line); i++) {
                if (line[i] != ' ')
                    printf("%c", alpha_map[line[i]-'a']);
                else
                    printf(" ");
            }
            printf("\n");
        }
        else {
            for (i = 0; i < strlen(line); i++) {
                if (line[i] != ' ')
                    printf("*");
                else
                    printf(" ");
            }
            printf("\n");
        }
    }

    return 0;
}
