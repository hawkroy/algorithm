#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 16
#define MAXNUM 1000

typedef struct COLOR_ {
	char col[STRLEN];
	int cnt;
}COLOR;

COLOR colors[MAXNUM];
int col_num = 0;

void init(void) {
	//memset(ballons.colors, 0, ballons.num);
	int i;
	for (i = 0; i < MAXNUM; ++i) {
		strcpy(colors[i].col, "");
		colors[i].cnt = 0;
	}
	col_num = 0;
	return ;
}

int main(int argc, char** argv) {
	int num = 0;
	int i, j;
	char temp_str[STRLEN];
	int max;
	int idx;
	
	while ((scanf("%d", &num)!= EOF) && num) {			// EOF is another stop condition
		init();
		
		for (i = 0; i < num; ++i) {
			scanf("%s", temp_str);
			
			for (j = 0; j < col_num; ++j) {
				if (!strcmp(colors[j].col, temp_str)) {
					++colors[j].cnt;
					break;
				}
			}
			if (j == col_num) {
				strcpy(colors[j].col, temp_str);
				++col_num;
			}
			
		}
		
		max = idx = 0;
		for (i = 0; i < col_num; ++i) {
			if (max < colors[i].cnt) {
				max = colors[i].cnt;
				idx = i;
			}
		}
		
		printf("%s\n", colors[idx].col);
	}
	
	return 0;
}
