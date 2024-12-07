#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define FUNNY_ARRAY_DIMENS 140

bool is_mas_cross(char* string) {
  return !strcmp(string, "MAS") || !strcmp(string, "SAM");
}

unsigned int
how_many_xmases(char xmas_matrix[FUNNY_ARRAY_DIMENS][FUNNY_ARRAY_DIMENS]) {
  char mas_check[4] = "_A_";
  unsigned int xmases = 0;

  for (int i = 1; i < FUNNY_ARRAY_DIMENS - 1; i++) {
    for (int j = 1; j < FUNNY_ARRAY_DIMENS - 1; j++) {
      if (xmas_matrix[i][j] != 'A')
        continue;
      mas_check[0] = xmas_matrix[i - 1][j - 1];
      mas_check[2] = xmas_matrix[i + 1][j + 1];
      if (!is_mas_cross(mas_check))
        continue;
      mas_check[0] = xmas_matrix[i + 1][j - 1];
      mas_check[2] = xmas_matrix[i - 1][j + 1];
      if (!is_mas_cross(mas_check))
        continue;
      xmases++;
    }
  }
  return xmases;
}

int main(void) {
  FILE* fptr = fopen("input.txt", "r");

  if (fptr == NULL) {
    perror("File doesn't exist.");
    return 1;
  }

  char buffer[FUNNY_ARRAY_DIMENS + 2];
  unsigned int times_mas_cross_appears = 0;
  char xmas_matrix[FUNNY_ARRAY_DIMENS][FUNNY_ARRAY_DIMENS];
  unsigned int row = 0;

  while (fgets(buffer, sizeof(buffer), fptr)) {
    if (!strcmp(buffer, "\n"))
      continue;
    strncpy(xmas_matrix[row], buffer, FUNNY_ARRAY_DIMENS);
    row++;
  }

  printf("MAS crosses: %d\n", how_many_xmases(xmas_matrix));
  fclose(fptr);
  return 0;
}
