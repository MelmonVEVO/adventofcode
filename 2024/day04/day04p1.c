#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define FUNNY_ARRAY_DIMENS 140

bool is_xmas(char* string) {
  return !strcmp(string, "XMAS") || !strcmp(string, "SAMX");
}

unsigned int
how_many_xmases(char xmas_matrix[FUNNY_ARRAY_DIMENS][FUNNY_ARRAY_DIMENS]) {
  char xmas_check[5];
  unsigned int xmases = 0;

  for (int i = 0; i < FUNNY_ARRAY_DIMENS; i++) {
    for (int j = 0; j < FUNNY_ARRAY_DIMENS; j++) {
      // HACK: There's definitely a better way to do this. Oh well!
      // RIGHT
      if (j + 3 < FUNNY_ARRAY_DIMENS) {
        strncpy(xmas_check, &xmas_matrix[i][j], 4);
        xmases += is_xmas(xmas_check);
      }

      // DOWN
      if (i + 3 < FUNNY_ARRAY_DIMENS) {
        xmas_check[0] = xmas_matrix[i][j];
        xmas_check[1] = xmas_matrix[i + 1][j];
        xmas_check[2] = xmas_matrix[i + 2][j];
        xmas_check[3] = xmas_matrix[i + 3][j];
        xmas_check[4] = '\0';
        xmases += is_xmas(xmas_check);
      }

      // DOWN RIGHT
      if ((i + 3 < FUNNY_ARRAY_DIMENS) && (j + 3 < FUNNY_ARRAY_DIMENS)) {
        xmas_check[0] = xmas_matrix[i][j];
        xmas_check[1] = xmas_matrix[i + 1][j + 1];
        xmas_check[2] = xmas_matrix[i + 2][j + 2];
        xmas_check[3] = xmas_matrix[i + 3][j + 3];
        xmas_check[4] = '\0';
        xmases += is_xmas(xmas_check);
      }

      // DOWN LEFT
      if ((i + 3 < FUNNY_ARRAY_DIMENS) && (j - 3 >= 0)) {
        xmas_check[0] = xmas_matrix[i][j];
        xmas_check[1] = xmas_matrix[i + 1][j - 1];
        xmas_check[2] = xmas_matrix[i + 2][j - 2];
        xmas_check[3] = xmas_matrix[i + 3][j - 3];
        xmas_check[4] = '\0';
        xmases += is_xmas(xmas_check);
      }
    }
  }

  return xmases;
}

int main(void) {
  FILE* fptr = fopen("input.txt", "r");

  if (fptr == NULL) {
    fclose(fptr);
    perror("File doesn't exist.");
    return 1;
  }

  char buffer[FUNNY_ARRAY_DIMENS + 2];
  unsigned int times_xmas_appears = 0;
  char xmas_matrix[FUNNY_ARRAY_DIMENS][FUNNY_ARRAY_DIMENS];
  unsigned int row = 0;

  while (fgets(buffer, sizeof(buffer), fptr)) {
    if (!strcmp(buffer, "\n"))
      continue;
    strncpy(xmas_matrix[row], buffer, FUNNY_ARRAY_DIMENS);
    row++;
  }

  printf("Xmases: %d", how_many_xmases(xmas_matrix));
  fclose(fptr);
  return 0;
}
