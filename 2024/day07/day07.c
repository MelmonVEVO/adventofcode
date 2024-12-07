#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;

struct Node {
  int value;
  Node* add;
  Node* concat;
  Node* mult;
};

Node* create_node(int value) {
  Node* new_node = (Node*)malloc(sizeof(Node));
  new_node->value = value;
  new_node->add = NULL;
  new_node->concat = NULL;
  new_node->mult = NULL;
  return new_node;
}

void free_node(Node* node) {
  if (node->add) {
    free_node(node->add);
  }
  if (node->concat) {
    free_node(node->concat);
  }
  if (node->mult) {
    free_node(node->mult);
  }
  free(node);
}

bool dfs(Node* node, int* nums, const unsigned int numlen,
         const int number_find) {
  if (numlen <= 1) {
    if (node->value == number_find) {
      return true;
    }
    return false;
  }
  int next_number = nums[1];
  node->add = create_node(next_number + node->value);
  node->mult = create_node(next_number * node->value);
  return dfs(node->add, nums + 1, numlen - 1, number_find) ||
         dfs(node->mult, nums + 1, numlen - 1, number_find);
}

int main(void) {
  FILE* fptr = fopen("input.txt", "r");

  if (fptr == NULL) {
    perror("File doesn't exist.");
    return 1;
  }

  char buffer[1000];
  long computable_total = 0;

  while (fgets(buffer, sizeof(buffer), fptr)) {
    if (!strcmp(buffer, "\n"))
      continue;

    char* token = strtok(buffer, " ");
    int tsize = strlen(token);
    char result_buffer[tsize];
    strncpy(result_buffer, token, tsize - 1);

    long equation_result = atol(result_buffer);
    int operands[50];
    unsigned int operand_len = 0;

    token = strtok(NULL, " ");

    while (token != NULL) {
      operands[operand_len] = atoi(token);
      operand_len++;
      token = strtok(NULL, " ");
    }

    Node* num_tree = create_node(operands[0]);
    if (dfs(num_tree, operands, operand_len, equation_result))
      computable_total += equation_result;
    free_node(num_tree);
  }

  fclose(fptr);

  printf("Computable total: %lu\n", computable_total);

  return 0;
}
