#include <stdio.h>
#include <string.h>

#define FUNNY_ARRAY_DIMENS 130
#define NOT_VISITED '.'
#define VISITED 'X'
#define OBSTACLE '#'

typedef struct {
  int x;
  int y;
} Vec2;

// Returns number of distinct positions
unsigned int traverse(char map[FUNNY_ARRAY_DIMENS][FUNNY_ARRAY_DIMENS],
                      Vec2 initial_position) {
  unsigned int unique_cells = 1;
  Vec2 current_position = initial_position;
  Vec2 guard_dir = (Vec2){.x = 0, .y = -1};

  map[initial_position.y][initial_position.x] = VISITED;

  while (1) {
    if (map[current_position.y][current_position.x] == NOT_VISITED) {
      unique_cells++;
      map[current_position.y][current_position.x] = VISITED;
    }

    Vec2 next = (Vec2){.x = current_position.x + guard_dir.x,
                       .y = current_position.y + guard_dir.y};

    if (next.x < 0 || next.x >= FUNNY_ARRAY_DIMENS || next.y < 0 ||
        next.y >= FUNNY_ARRAY_DIMENS) {
      break;
    }

    if (map[next.y][next.x] == OBSTACLE) {
      guard_dir = (Vec2){.x = -guard_dir.y, .y = guard_dir.x};
      continue;
    }

    current_position = next;
  }

  return unique_cells;
}

int main(void) {
  FILE* fptr = fopen("input.txt", "r");

  if (fptr == NULL) {
    perror("File doesn't exist.");
    return 1;
  }

  char buffer[FUNNY_ARRAY_DIMENS + 2];
  char map[FUNNY_ARRAY_DIMENS][FUNNY_ARRAY_DIMENS];
  unsigned int row = 0;
  Vec2 init_position = (Vec2){.x = -1, .y = -1};
  // The output of this while loop is a bit dubious, but I got the correct
  // answer so so I'm keeping it like this until I complete the challenge.
  while (fgets(buffer, sizeof(buffer), fptr)) {
    if (!strcmp(buffer, "\n"))
      continue;
    strncpy(map[row], buffer, FUNNY_ARRAY_DIMENS);
    int init_idx = strcspn(buffer, "^");
    if (init_idx < FUNNY_ARRAY_DIMENS + 1) {
      init_position = (Vec2){.x = init_idx, .y = row};
      map[row][init_idx] = NOT_VISITED;
    }
    printf("%s\n", map[row]);
    row++;
  }

  if (init_position.x == -1) {
    perror("Initial position was not determined.");
    return 1;
  }

  printf("Distinct cells visited: %d", traverse(map, init_position));

  fclose(fptr);

  return 0;
}
