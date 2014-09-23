/*
 * See the Concrete Math Chapter #1
 * Best!!!!!
 * cyclic-prefix will occur not in header.........
 * refer a = 2, b = 7
 */

#include <stdio.h>
#include <stdlib.h>

#define MOD 7
#define MAXNUM (MOD*MOD+2)

int f[MAXNUM];
int find[MOD][MOD];

int main(int argc, char** argv) {
	int a, b, n;
	int i;
	int cycle;
	int result;
	
#ifndef ONLINE_JUDGE
	int j;
#endif
	
	while ((scanf("%d %d %d", &a, &b, &n) != EOF) && (a+b+n)) {
		if (n == 1 || n == 2) {
			printf("%d\n", 1);
			continue;
		}
		
		memset(find, 0, sizeof(find));

#ifndef ONLINE_JUDGE
		for ( i = 0; i < MOD; ++i) {
			for (j = 0; j < MOD; ++j)
				printf("%d ", find[i][j]);
		}
		printf("\n");
#endif

		f[1] = f[2] = 1;
		find[1][1] = 1;
		for (i = 3; i < MAXNUM; ++i) {
			f[i] = (a*f[i-1]+b*f[i-2]) % MOD;
			if (find[f[i-1]][f[i]] == 0 ) {
				find[f[i-1]][f[i]] = i-1;
			}
			else {
				break;
			}
		}
		
#ifndef ONLINE_JUDGE
		printf("(i-1) = %d, find[%d][%d] = %d\n", i-1, i-1, i, find[f[i-1]][f[i]]);
#endif
		
		// find cyclic time
		cycle = i-1 - find[f[i-1]][f[i]];
		
#ifndef ONLINE_JUDGE
		for (j = 0; j < MAXNUM; ++j) {
			printf("%d ", f[j]);
		}
		printf("\n");
		printf("cyclic %d\n", cycle);
#endif
		
		if (n < find[f[i-1]][f[i]]) {
			result = n;
		}
		else {
			result = (n-find[f[i-1]][f[i]])%cycle + find[f[i-1]][f[i]];
		}
		printf("%d\n", f[result]);
	}
	
	return 0;
}
