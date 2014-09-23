#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_LETTER_LEN  5
#define MAX_LETTER_LEN  12

int target;
char letters[MAX_LETTER_LEN+1];
int nums[MAX_LETTER_LEN+1];

/*
 * formular: 
 *    v-w^2+x^3-y^4+z^5 = target
 *    descending order if many match
 */
void resolve(void) {
  int i, j;
  int temp;
  int v, w, x, y, z;
  int letter_len = strlen(letters);

  for (i = 0; i < letter_len; i++) {
    nums[i] = letters[i] - 'A' + 1;
  }
  
  // sort for descending order
  for (i = 0; i < letter_len; i++) {
    for (j = i+1; j < letter_len; j++) {
      if (nums[i] < nums[j]) {
        temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
      }
    }
  }

#ifdef _DEBUG
  printf("sort array is: ");
  for (i = 0; i < letter_len; i++) {
    printf("%c ", nums[i]-1+'A');
  }
  printf("\n");
#endif
  
  // enum the result
  for (v = 0; v < letter_len; v++) {
    for (w = 0; w < letter_len; w++) {
      if (w == v) {
        continue;
      }
      for (x = 0; x < letter_len; x++) {
        if (x == w || x == v) {
          continue;
        }
        for (y = 0; y < letter_len; y++) {
          if (y == x || y == w || y == v) {
            continue;
          }
          for (z = 0; z < letter_len; z++) {
            if (z == y || z == x || z == w || z == v) {
              continue;
            }
            temp = nums[v] - nums[w]*nums[w] 
                    + nums[x]*nums[x]*nums[x] 
                    - nums[y]*nums[y]*nums[y]*nums[y] 
                    + nums[z]*nums[z]*nums[z]*nums[z]*nums[z];
            if (temp == target) {
              printf("%c%c%c%c%c\n", 
                  nums[v]-1+'A', nums[w]-1+'A', 
                  nums[x]-1+'A', nums[y]-1+'A', nums[z]-1+'A');
              return ;
            }
          }
        }
      }
    }
  }
  
  printf("no solution\n");

  return;
}

int main(int argc, char * argv[]) {
  while (1) {
    target = 0;
    if (fscanf(stdin, "%d %s", &target, letters) == EOF) {
      break;
    }

#ifdef _DEBUG
    printf("input is: %d %s\n", target, letters);
    printf("char array len: %d\n", strlen(letters));
#endif

    if (target == 0 && strcmp(letters, "END") == 0) {
      break;
    }

    resolve();
  }
  return 0;
}
