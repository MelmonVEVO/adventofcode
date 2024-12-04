#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************************/
/*   Abandon hope all    */
/*   ye who enter here   */
/*************************/

int compare(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

int main(void) {
  FILE* fptr = fopen("day01-data.txt", "r");

  if (fptr == NULL) {
    fclose(fptr);
    return 1;
  };

  int list1[1000];
  int list2[1000];

  unsigned short cursor = 0;

  char* line = NULL;
  size_t len;
  ssize_t read;

  char num1s[6];
  char num2s[6];

  while ((read = getline(&line, &len, fptr)) != -1) {
    if (*line == '\n')
      break;
    strncpy(num1s, line, 5);
    strncpy(num2s, line + 8, 5);
    num1s[5] = '\0';
    num2s[5] = '\0';
    list1[cursor] = atoi(num1s);
    list2[cursor] = atoi(num2s);
    cursor++;
  }

  fclose(fptr);

  qsort(list1, 1000, sizeof(int), compare);
  qsort(list2, 1000, sizeof(int), compare);

  unsigned int total = 0;

  for (unsigned int cursor2 = 0; cursor2 < 1000; cursor2++) {
    total += abs(list1[cursor2] - list2[cursor2]);
  }

  if (line)
    free(line);

  printf("Total: %d", total);

  return 0;
}
