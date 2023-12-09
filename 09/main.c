#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

#define CAP 32

int extrapolate(int *arr, size_t len) {
  bool all_zeros = true;

  for (size_t i = 0; i < len && all_zeros; ++i) {
    if (arr[i] != 0) all_zeros = false;
  }

  if (all_zeros) return 0;

  int *new_arr = malloc(sizeof(int) * (len - 1));

  for (size_t i = 0; i < len - 1; ++i) {
    new_arr[i] = arr[i + 1] - arr[i];
  }

  int val = arr[len - 1] + extrapolate(new_arr, len - 1);

  free(new_arr);

  return val;
}

void part1(FILE *fp) {
  char buf[128];
  int numbers[CAP];
  size_t len = 0;
  int ans = 0;

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    len = 0;

    char *tok = strtok(buf, " ");

    while (tok != NULL) {
      numbers[len++] = atoi(tok);
      tok = strtok(NULL, " ");
    }

    ans += extrapolate(numbers, len);
  }

  printf("Part 1: %d\n", ans);
}

void reverse(int *arr, size_t len) {
  for (size_t i = 0; i < len / 2; ++i) {
    int tmp = arr[i];
    arr[i] = arr[len - i - 1];
    arr[len - i - 1] = tmp;
  }
}

void part2(FILE *fp) {
  char buf[128];
  int numbers[CAP];
  size_t len = 0;
  int ans = 0;

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    len = 0;

    char *tok = strtok(buf, " ");

    while (tok != NULL) {
      numbers[len++] = atoi(tok);
      tok = strtok(NULL, " ");
    }

    reverse(numbers, len);

    ans += extrapolate(numbers, len);
  }

  printf("Part 2: %d\n", ans);
}

int main(void) {
  FILE *fp = fopen(FILENAME, "r");

  part1(fp);
  rewind(fp);
  part2(fp);

  fclose(fp);
  return 0;
}
