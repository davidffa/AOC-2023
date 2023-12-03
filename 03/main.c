#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

#define CAP 256

int dirs[8][2] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1},
    {1, 1},
    {-1, -1},
    {1, -1},
    {-1, 1},
};

static char matrix[CAP][CAP];
static bool vis[CAP][CAP];
static int rows = 0, cols = 0;

int get_number(int r, int c) {
  int c0 = c;

  while (c0 < cols) {
    if (!isdigit(matrix[r][c0 + 1])) break;
    c0++;
  }

  int n = 0;
  int digit_pos = 0;
  int digit;

  while (c0 >= 0) {
    if (!isdigit(matrix[r][c0])) break;

    vis[r][c0] = true;
    digit = matrix[r][c0] - '0';

    n += powf(10, digit_pos) * digit;

    digit_pos++;
    c0--;
  }

  return n;
}

void read_input(FILE* fp) {
  while (fgets(matrix[rows], CAP, fp) != NULL) {
    cols = strlen(matrix[rows]) - 1;

    rows++;
  }
}

void part1(void) {
  memset(vis, false, sizeof(vis));
  int sum = 0;

  int r0, c0;

  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (matrix[r][c] == '.' || isdigit(matrix[r][c])) continue;

      for (int i = 0; i < 8; ++i) {
        r0 = r + dirs[i][0], c0 = c + dirs[i][1];

        if (r0 >= 0 && r0 < rows && c0 >= 0 && c0 < cols) {
          if (!isdigit(matrix[r0][c0]) || vis[r0][c0]) continue;

          sum += get_number(r0, c0);
        }
      }
    }
  }

  printf("Part 1: %d\n", sum);
}

void part2(void) {
  memset(vis, false, sizeof(vis));
  int sum = 0;

  int r0, c0;

  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (matrix[r][c] != '*') continue;

      int nums[2] = {0};
      int num_count = 0;

      for (int i = 0; i < 8 && num_count < 2; ++i) {
        r0 = r + dirs[i][0], c0 = c + dirs[i][1];

        if (r0 >= 0 && r0 < rows && c0 >= 0 && c0 < cols) {
          if (!isdigit(matrix[r0][c0]) || vis[r0][c0]) continue;

          nums[num_count++] = get_number(r0, c0);
        }
      }

      if (num_count == 2) {
        sum += nums[0] * nums[1];
      }
    }
  }

  printf("Part 2: %d\n", sum);
}

int main(void) {
  FILE* fp = fopen(FILENAME, "r");

  read_input(fp);

  fclose(fp);

  part1();
  part2();
}
