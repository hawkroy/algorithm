#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int numer;
int denom;

void calc_e(int n) {
  int ret;
  int cnt = 0;
  char value[20];

  if (n == 0) {
    numer = 1;
    denom = 1;
  }
  else {
    numer = numer * n + 1;
    denom *= n;
  }

  ret = numer / denom;
  if (numer == (ret*denom)) {
    sprintf(value, "%d", numer/denom);
  }
  else {
    sprintf(value, "%.09f", (double)(1.0*numer/denom));
  }

  for (ret = strlen(value)-1; ret >= 0; ret--) {
    if (value[ret] != '0') {
      break;
    }
    cnt++;
  }

  if (ret < strlen(value)-1 && cnt > 1) {
    value[++ret] = '\0';
  }

  printf("%d %s\n", n, value);

  return ;
}

int main(int argc, char * argv[]) {
  int i;
  
  printf("n e\n");
  printf("- -----------\n");

  for (i = 0; i <10; i++) {
    calc_e(i);
  }

  return 0;
}
