#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int a, b;

int gcd(int a, int b) {
  int t;

  if (a < b) {
    t = a;
    a = b;
    b = t;
  }

  while (b != 0 ){
    t = b;
    b = a % b;
    a = t;
  }

  return a;
}

int main(int argc, char * argv[]) {
  while (scanf("%d %d", &a, &b) != EOF) {
#if 1    
    if (gcd(a,b) == 1) {
      printf("%10d%10d    %s\n", a, b, "Good Choice");
    }
    else {
      printf("%10d%10d    %s\n", a, b, "Bad Choice");
    }
    printf("\n");
#else
    printf("gcd number is: %d\n", gcd(a, b));
#endif

  }

  return 0;
}
