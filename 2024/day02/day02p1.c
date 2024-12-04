#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DISREGARD -999999

typedef enum { DECREASING, INCREASING, IDK } Ordering;

// Returns 1 if not safe, 0 if it is.
unsigned int is_safe(char* buf) {
  char* token = strtok(buf, " ");
  Ordering ordering = IDK;
  int previous_number = DISREGARD;
  while (token != NULL) {
    int current_number = atoi(token);

    if (previous_number == DISREGARD) {
      previous_number = current_number;
      token = strtok(NULL, " ");
      continue;
    }

    if (abs(current_number - previous_number) > 3 ||
        current_number - previous_number == 0)
      return 0;
    if (ordering == IDK) {
      ordering = previous_number > current_number ? DECREASING : INCREASING;
    } else if (ordering == DECREASING && previous_number < current_number ||
               ordering == INCREASING && previous_number > current_number)
      return 0;
    previous_number = current_number;
    token = strtok(NULL, " ");
  }
  return 1;
}

int main(void) {
  FILE* fptr = fopen("input.txt", "r");

  if (fptr == NULL) {
    fclose(fptr);
    perror("File doesn't exist.");
    return 1;
  }

  char buf[256];
  unsigned int safe_reports = 0;

  while (fgets(buf, sizeof(buf), fptr)) {
    if (strcmp(buf, "\n") == 0)
      continue;
    safe_reports += is_safe(buf);
  }

  fclose(fptr);

  printf("Safe reports: %d", safe_reports);
  return 0;
}
