#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 20

int primes[2*MAX_NUM];
int used[MAX_NUM];
int result[MAX_NUM];
int n;

void init_prime(void) {
  int i, j;
  int visited[2*MAX_NUM];

  memset(visited, sizeof(visited)/sizeof(int), 0);
  memset(primes, sizeof(primes)/sizeof(int), 0);

  for (i = 2; i < sizeof(primes)/sizeof(int); i++) {
    if (visited[i] == 1) {
      continue;
    }

    primes[i] = 1;
    
    j = i;
    while (j < sizeof(visited)/sizeof(int)) {
      visited[j] = 1;
      j += i;
    }
  }

#ifdef _DEBUG
  printf("the prime list is:\n");
  for (i = 0; i < sizeof(primes)/sizeof(int); i++) {
    if (primes[i] == 1) {
      printf("%d ", i);
    }
  }
  printf("\n");
#endif

  return ;
}

void solve(int index) {
  int i, j;

//  for (j = 0; j < index; j++) {
//    printf("%d ", result[j]);
//  }
//  printf("\n");

  for (i = 2; i <= n; i++) {
    if (used[i] == 1) {
      continue;
    }

    if (primes[result[index-1]+i] == 1) {
      used[i] = 1;
      result[index] = i;

      if (index == (n-1)) {
        if (primes[result[index]+result[0]] == 1) {
          for (j = 0; j < (n-1); j++) {
            printf("%d ", result[j]);
          }
          printf("%d\n", result[j]);
        }
      }
      else {
        solve(index+1);
      }

      used[i] = 0;
    }
  }

  return ;
}

int main(int argc, char *argv[]) {
  int casen = 1;

  init_prime();

  while (scanf("%d\n", &n) != EOF) {
    result[0] = 1;
    used[1] = 1;
    memset(used, sizeof(used)/sizeof(int), 0);
    printf("Case %d:\n", casen++);
    solve(1);
    printf("\n");
  }

  return 0;
}
