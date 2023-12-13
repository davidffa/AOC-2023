#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

#define CAP 32

static char grid[CAP][CAP];
static int rows, cols;

int solve(int part) {
  // Check vertical mirroring
  for (int c = 1; c < cols; ++c) {
    int diff_symbols = 0;

    for (int c1 = c - 1, c2 = c; c1 >= 0 && c2 < cols; --c1, ++c2) {
      if (part == 1 && diff_symbols != 0) break;
      if (part == 2 && diff_symbols > 1) break;

      for (int r = 0; r < rows; ++r) {
        if (grid[r][c1] != grid[r][c2]) {
          ++diff_symbols;
        }
      }
    }

    if (part == 1 && diff_symbols == 0)
      return c;
    else if (part == 2 && diff_symbols == 1)
      return c;
  }

  // Check horizontal mirroring
  for (int r = 1; r < rows; ++r) {
    int diff_symbols = 0;

    for (int r1 = r - 1, r2 = r; r1 >= 0 && r2 < rows; --r1, ++r2) {
      if (part == 1 && diff_symbols != 0) break;
      if (part == 2 && diff_symbols > 1) break;

      for (int c = 0; c < cols; ++c) {
        if (grid[r1][c] != grid[r2][c]) {
          ++diff_symbols;
        }
      }
    }

    if (part == 1 && diff_symbols == 0)
      return 100 * r;
    else if (part == 2 && diff_symbols == 1)
      return 100 * r;
  }

  return 0;
}

void part1(FILE *fp) {
  int ans = 0;
  rows = 0, cols = 0;
  char buf[CAP];

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    if (buf[0] == '\n') {
      ans += solve(1);
      rows = 0;
      cols = 0;
      continue;
    }

    int len = strlen(buf);

    if (rows == 0) {
      cols = len - 1;
    }

    memcpy(grid[rows++], buf, cols);
  }

  ans += solve(1);

  printf("Part 1: %d\n", ans);
}

void part2(FILE *fp) {
  int ans = 0;
  rows = 0, cols = 0;
  char buf[CAP];

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    if (buf[0] == '\n') {
      ans += solve(2);
      rows = 0;
      cols = 0;
      continue;
    }

    int len = strlen(buf);

    if (rows == 0) {
      cols = len - 1;
    }

    memcpy(grid[rows++], buf, cols);
  }

  ans += solve(2);

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
