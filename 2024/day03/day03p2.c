#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MUL_REGEX "mul\\([0-9]+,[0-9]+\\)"

// Nums must be in format "x,y"
int multiply_nums_string(char* nums) {
  int l = strlen(nums);
  char left[l];
  char right[l];

  size_t comma = strcspn(nums, ",");
  strncpy(left, nums, comma);
  strcpy(right, nums + comma + 1);

  int i1 = atoi(left);
  int i2 = atoi(right);

  return i1 * i2;
}

int multiply_reader(char* buffer, regex_t compiled_regex) {
  regmatch_t group_array[1];
  int total = 0;

  while (!regexec(&compiled_regex, buffer, 1, group_array, 0)) {
    regoff_t start = group_array[0].rm_so;
    regoff_t end = group_array[0].rm_eo;

    char* nums = (char*)malloc(sizeof(char) * (end - start));

    strncpy(nums, buffer + start + 4, end - start - 5);

    total += multiply_nums_string(nums);

    buffer += end;

    free(nums);
  }

  return total;
}

int main(void) {
  FILE* fptr = fopen("input.txt", "r");

  if (fptr == NULL) {
    fclose(fptr);
    perror("File doesn't exist.");
    return 1;
  }

  char buffer[5000];
  int total = 0;
  regex_t regex_compiled;

  if (regcomp(&regex_compiled, MUL_REGEX, REG_EXTENDED)) {
    perror("Something went wrong with regex compilation!");
    return 1;
  }

  while (fgets(buffer, sizeof(buffer), fptr)) {
    if (!strcmp(buffer, "\n"))
      continue;
    total += multiply_reader(buffer, regex_compiled);
  }

  fclose(fptr);
  regfree(&regex_compiled);

  printf("Total multiplied values: %d\n", total);

  return 0;
}
