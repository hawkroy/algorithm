#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

#define SWAP(a, b) {a = a^b; b = a^b; a = a^b;}

uint64_t gcd(uint64_t a, uint64_t b) {
    if (a < b)
        SWAP(a,b);
        
    if (b == 0)
        return a;
    else
        return gcd(b, a%b);
}

uint64_t nlcm(uint32_t * array, int num) {
    uint64_t ret;
    int i;
    
    ret = (uint64_t)array[0];
    i = 1;
    
    while (i < num)  {
        ret = ret / gcd(ret, (uint64_t)array[i]) * (uint64_t)array[i];
        i++;
    }
    
    return ret;   
}

int main(int argc, char ** argv) {
    int ncases, num, temp_num;
    int i;
    uint32_t *array;
    uint64_t ret;
    
    scanf("%d", &ncases);
    
    num = 0;
    while (ncases -- > 0) {
        scanf("%d", &temp_num);
        
        if (temp_num > num) {
            array = (uint32_t *)realloc(array, sizeof(uint32_t)*temp_num); 
        }
        
        num = temp_num;
        
        for (i = 0; i < num; i++) {
            scanf("%d", &array[i]);
        }
        
#ifndef ONLINE_JUDGE
        for (i = 0; i < num; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
#endif
        
        ret = nlcm(array, num);
        
        printf("%ld\n", ret);
        
    }
    
    free(array);
    array = NULL;
    
    return 0;
}
