#include <stdio.h>

int main(void) {
  FILE* fptr = fopen("test_input.txt", "r");
  if (!fptr) {
    fclose(fptr);
    perror("File doesn't exist.");
    return 1;
  }

  char buffer[500];

  while (fgets(buffer, sizeof(buffer), fptr)) {
  }

  return 0;
}
