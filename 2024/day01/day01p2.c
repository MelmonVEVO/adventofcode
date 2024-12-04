#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  FILE* fptr = fopen("day01-data.txt", "r");

  if (fptr == NULL) {
    fclose(fptr);
    return 1;
  }

  // HACK: Way too much memory is used here. I'm too lazy to implement an actual
  // hashmap. Oh well!
  unsigned short rightlist_occurances[99999] = {0};
  int leftlist[1000];

  char* line = NULL;
  size_t len;
  ssize_t read;

  char num1s[6];
  char num2s[6];

  unsigned short cursor = 0;

  unsigned int similarity_score = 0;

  while ((read = getline(&line, &len, fptr)) != -1) {
    if (*line == '\n')
      break;
    strncpy(num1s, line, 5);
    strncpy(num2s, line + 8, 5);
    num1s[5] = '\0';
    num2s[5] = '\0';
    leftlist[cursor] = atoi(num1s);
    unsigned int tmp = atoi(num2s);
    rightlist_occurances[tmp]++;
    cursor++;
  }

  fclose(fptr);

  for (unsigned short cursor2 = 0; cursor2 < 1000; cursor2++) {
    similarity_score +=
        leftlist[cursor2] * rightlist_occurances[leftlist[cursor2]];
  }

  if (line)
    free(line);

  printf("Similarity: %d", similarity_score);

  return 0;
}
