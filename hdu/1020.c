#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#define MAXNUM 10000

char str[MAXNUM];

int main(int argc, char** argv) {
    int num, index, copy;
    char chr;
    int i;
    
    scanf("%d", &num);
    
    while (num-- > 0) {
        scanf("%s", str);
        
        index = 0;
        while (index < strlen(str)) {
            
            copy = 0;
            chr = str[index];
            
            // condition not clear for reader, can change to another form
            while ((chr == str[index]) && (index < strlen(str))) {
                copy++;
                index++;
            }
            
            if (copy == 1)
                printf("%c", chr);
            else
                printf("%d%c", copy, chr);
        }
         
        printf("\n");
    }
    
    return 0;
}
