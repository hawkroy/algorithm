#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * use integer to represent bit0-6
 * ---0---
 * |     |
 * 1     2
 * |     |
 * ---3---
 * |     |
 * 4     5
 * |     |
 * ---6---
 */
int led_format[] =
{
    0b1110111,  /*0*/
    0b0100100,  /*1*/
    0b1011101,  /*2*/
    0b1101101,  /*3*/
    0b0101110,  /*4*/
    0b1101011,  /*5*/
    0b1111011,  /*6*/
    0b0100101,  /*7*/
    0b1111111,  /*8*/
    0b1101111   /*9*/
};

char str[10];
int s;

void output_line(int line)
{
    int i, j;
    char left, middle, right;

    for (i = 0; i < strlen(str); i++) {
        if (line == 0) {
            if (led_format[str[i]-'0'] & 0x1)
                middle = '-';
            else
                middle = ' ';
            left = ' ';
            right = ' ';
        }
        else if (line == s+1) {
            if (led_format[str[i]-'0'] & 0x8)
                middle = '-';
            else
                middle = ' ';
            left = ' ';
            right = ' ';
        }
        else if (line == 2*s+2) {
            if (led_format[str[i]-'0'] & 0x40)
                middle = '-';
            else
                middle = ' ';
            left = ' ';
            right = ' ';
        }
        else if (line > 0 && line < s+1) {
            if (led_format[str[i]-'0'] & 0x2)
                left = '|';
            else
                left = ' ';
            if (led_format[str[i]-'0'] & 0x4)
                right = '|';
            else
                right = ' ';
            middle = ' ';
        }
        else if (line > s+1 && line < 2*s+2) {
            if (led_format[str[i]-'0'] & 0x10)
                left = '|';
            else
                left = ' ';
            if (led_format[str[i]-'0'] & 0x20)
                right = '|';
            else
                right = ' ';
            middle = ' ';
        }

        printf("%c", left);
        for (j = 0; j < s; j++)
            printf("%c", middle);
        printf("%c", right);
        if (i != strlen(str)-1)
            printf(" ");
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    int i;
    while (scanf("%d %s", &s, str) != EOF) {
        if (s == 0 && str[0] == '0')
            break;

        for (i = 0; i < 2*s+3; i++)
            output_line(i);

        printf("\n");
    }

    return 0;
}
