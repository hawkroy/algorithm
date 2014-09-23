#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10

char buf[MAX_SIZE];

int main(int argc, char * argv[]) {
  char *newline;
  unsigned char line;
  unsigned char digit;
  int i;

  digit = 0;
  line = 0;
  newline = NULL;
  while (fgets(buf, MAX_SIZE, stdin) != NULL) {
    if (buf[0] == '0') {
      break;
    }

    newline = strstr(buf, "\n");
    if (newline != NULL) {
      *newline = '\0';
      line = 1;
    }
    else {
      buf[MAX_SIZE-1] = '\0';
    }

#ifdef _DEBUG
    printf("input string is: %s\n", buf);
    if (line == 1) {
      printf("it is the end of one number\n");
    }
#endif

    for (i = 0; i < strlen(buf); i++) {
      digit += buf[i]-'0';
      // optimize: we can trust the digit no more than 20
      //           add two number we calc the root, the same
      //           as calc sum and calc root
      if (digit > 9) {
        digit = digit%10 + 1;
      }
    }

    if (line == 1) {
      printf("%d\n", digit);
      digit = 0;
      line = 0;
    }
  }

  return 0;
}
