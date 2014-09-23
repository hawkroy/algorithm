#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXLEN 100000
//#undef max
//#define max(a,b) (((a)>(b))? (a): (b))

typedef struct RESULT_ {
	long sum;	// max sum
	int l;		// low indicator
	int h;		// high indicator
}RESULT;

int array[MAXLEN];

RESULT find_max(int size) {
	long max_sofar = INT_MIN;
	long max_cur = 0;
	int i;
	int l, h;
	RESULT ret;
	
	l = h = 0;
	for (i = 0; i < size; ++i) {
		max_cur += array[i];
		//max_cur = max(max_cur, 0);
		if (max_cur > max_sofar) {
			max_sofar = max_cur;
			ret.h = i;
			ret.l = l;
		}
		if (max_cur < 0) {
			max_cur = 0;
			l = h = (i+1);
		}
	}
	
	ret.sum = max_sofar;
	ret.h += 1;
	ret.l += 1;
	
	return ret;
}

int main(int argc, char** argv) {
        int n, headcnt, i, cnt;
        RESULT ret;
#ifdef NO_ONLINE
	int dbg_i;
#endif
        
        cnt = 1;
        scanf("%d", &n);
        while (n-->0) {
        	scanf("%d", &headcnt);
        	//memset(array, 0, MAXLEN);
        	i = 0;
        	while (i < headcnt) {
        		scanf("%d", &array[i++]);
        	}
#ifdef NO_ONLINE
        	for (dbg_i = 0; dbg_i < headcnt; ++dbg_i) {
        		printf("%d ", array[dbg_i]);
        	}
        	printf("\n");
#endif
        	ret = find_max(headcnt);
        	printf("Case %d:\n", cnt++);
        	printf("%d %d %d\n", ret.sum, ret.l, ret.h);
        	if (n)
        		printf("\n");
        }
        
        return 0;
}
