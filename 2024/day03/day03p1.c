#include <regex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MUL_REGEX "^mul\\(\\d+,\\d+\\)$"

unsigned int multiply_reader(char* buffer, regex_t compiled_regex) {
  regmatch_t group_array[1];
  unsigned int total;
  char* nums;

  while (!regexec(&compiled_regex, buffer, 1, group_array, 0)) {
    regoff_t start = group_array[0].rm_so;
    regoff_t end = group_array[0].rm_eo;

    strncpy(nums, buffer + start, end - start + 3);

    printf("%s", nums);

    buffer += end;
  }

  free(nums);

  return total;
}

int main(void) {
  FILE* fptr = fopen("test_input.txt", "r");

  if (fptr == NULL) {
    fclose(fptr);
    perror("File doesn't exist.");
    return 1;
  }

  char buffer[5000];
  unsigned int total = 0;
  regex_t regex_compiled;

  if (regcomp(&regex_compiled, MUL_REGEX, REG_EXTENDED)) {
    perror("Something went wrong with regex compilation!");
    return 1;
  }

  while (fgets(buffer, sizeof(buffer), fptr)) {
    total += multiply_reader(buffer, regex_compiled);
  }

  fclose(fptr);
  regfree(&regex_compiled);

  printf("Total multiplied values: %d", total);

  return 0;
}
