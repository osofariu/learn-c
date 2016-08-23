#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

short int containsNonNumeric(const char* candidate) {
  int i;
  for (i = 0; i < strlen(candidate); i++) {
    if (candidate[i] < '0' || candidate[i] > '9') {
      return 1;
    }
  }
  return 0;
}

short int isEmptyString(const char* candidate) {
  return (strlen(candidate) == 0);
}

short int isConversionError(const char* input, int output) {
  return (isEmptyString(input) || containsNonNumeric(input));
}

short makeInt(const char* candidate, long* output) {
  int result = strtol(candidate, NULL, 10);
  *output = result;
  
  if (isConversionError(candidate, *output))
    return -1;
  else if (result == LONG_MIN) 
    return -2;
  else if (result == LONG_MAX)
    return -3;

  return 0;
}

int run_hello(int argc, char* argv[]) {
  int c;
  for (c=0; c < argc; c++) {
    printf("Arg %d is: %s\n", c, argv[c]);
  }
  printf("%d args printed\n", argc);

  if (argc > 1) {
    long out;
    int result = makeInt(argv[1], &out);
    if (result == 0)
      printf("Successful conversion to long: %ld\n", out);
    else if (result == -1)
      printf("Failed to convert, because input string container non-digit character\n");
    else if (result == -2)
      printf("Underflow: input was numberic but too small for a LONG\n");
    else if (result == -3)
      printf("Overflow: input was numberic but too large for a LONG\n");
    else
      printf("Some error code was returned that I didn't expect");
  }

  return 0;
}
