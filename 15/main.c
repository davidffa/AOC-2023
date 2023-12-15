#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample2.txt"
#endif

#define CAP 32768
#define BOOK_CAP 256

typedef struct {
  char label[16];
  uint8_t focal_len;
} Lens;

struct Node {
  Lens item;
  struct Node *next;
};

typedef struct Node Node;

Node *create_node(char *label, uint8_t focal_len) {
  Node *node = malloc(sizeof(Node));

  strcpy(node->item.label, label);
  node->item.focal_len = focal_len;
  node->next = NULL;

  return node;
}

void destroy_list(Node *head) {
  if (head == NULL) return;

  Node *prev = head;
  Node *cur = head;

  while (cur->next != NULL) {
    cur = cur->next;

    free(prev);

    prev = cur;
  }
}

int hash(char *str) {
  int h = 0;

  for (size_t i = 0; i < strlen(str); ++i) {
    h = ((h + str[i]) * 17) % 256;
  }

  return h;
}

void part1(FILE *fp) {
  char buf[CAP];
  int sum = 0;

  fscanf(fp, "%s", buf);

  char *tok = strtok(buf, ",");

  do {
    sum += hash(tok);
  } while ((tok = strtok(NULL, ",")) != NULL);

  printf("Part 1: %d\n", sum);
}

void part2(FILE *fp) {
  char buf[CAP];
  Node *book[BOOK_CAP] = {0};
  int sum = 0, box;

  fscanf(fp, "%s", buf);

  char *tok = strtok(buf, ",");
  char str[16];

  do {
    strcpy(str, tok);

    size_t l = strlen(str);

    if (str[l - 1] == '-') {
      str[l - 1] = '\0';

      box = hash(str);

      Node *head = book[box];

      if (head == NULL) continue;
      if (strcmp(head->item.label, str) == 0) {
        book[box] = head->next;
        free(head);
        continue;
      }

      while (head->next != NULL) {
        if (strcmp(head->next->item.label, str) == 0) {
          Node *next = head->next->next;
          free(head->next);
          head->next = next;
          break;
        }

        head = head->next;
      }
    } else {
      uint8_t focal_len = str[l - 1] - '0';
      str[l - 2] = '\0';

      box = hash(str);

      Node *head = book[box];
      Node *prev = head;
      bool element_found = false;

      while (head != NULL) {
        if (strcmp(head->item.label, str) == 0) {
          head->item.focal_len = focal_len;
          element_found = true;
          break;
        }

        prev = head;
        head = head->next;
      }

      if (element_found) continue;

      if (prev == NULL) {
        book[box] = create_node(str, focal_len);
      } else {
        prev->next = create_node(str, focal_len);
      }
    }
  } while ((tok = strtok(NULL, ",")) != NULL);

  for (int i = 0; i < BOOK_CAP; ++i) {
    if (book[i] != NULL) {
      // printf("Box %d:\n", i);

      Node *head = book[i];
      int slot = 1;

      while (head != NULL) {
        sum += (i + 1) * slot * head->item.focal_len;
        // printf("%s %d\n", head->item.label, head->item.focal_len);
        head = head->next;
        ++slot;
      }
    }

    destroy_list(book[i]);
  }

  printf("Part 2: %d\n", sum);
}

int main(void) {
  FILE *fp = fopen(FILENAME, "r");

  part1(fp);
  rewind(fp);
  part2(fp);

  fclose(fp);
  return 0;
}
