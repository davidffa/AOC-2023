#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#define SPACE 1000000
#else
#define FILENAME "sample.txt"
#define SPACE 10
#endif

#define CAP 256
#define ll long long

static char grid[CAP][CAP];
static bool vis[CAP][CAP];
static bool empty_rows[CAP];
static bool empty_cols[CAP];
static int rows = 0, cols = 0;

ll solve(int space) {
  ll ans = 0;
  int real_r = 0, real_c = 0;
  for (int r = 0; r < rows; ++r) {
    real_c = 0;
    for (int c = 0; c < cols; ++c) {
      if (grid[r][c] == '#' && !vis[r][c]) {
        vis[r][c] = true;

        int real_c0 = 0, real_r0 = 0;

        for (int r0 = 0; r0 < rows; ++r0) {
          real_c0 = 0;
          for (int c0 = 0; c0 < cols; ++c0) {
            if (grid[r0][c0] == '#' && !vis[r0][c0]) {
              ans += abs(real_r0 - real_r) + abs(real_c0 - real_c);
            }

            real_c0 += 1 + space * (int)empty_cols[c0];
          }
          real_r0 += 1 + space * (int)empty_rows[r0];
        }
      }
      real_c += 1 + space * (int)empty_cols[c];
    }
    real_r += 1 + space * (int)empty_rows[r];
  }

  return ans;
}

void part1(FILE *fp) {
  memset(empty_rows, true, sizeof(empty_rows));
  memset(empty_cols, true, sizeof(empty_cols));
  memset(vis, false, sizeof(vis));

  int ans = 0;

  while (fscanf(fp, "%s\n", grid[rows]) == 1) {
    if (rows == 0)
      cols = strlen(grid[0]);

    for (int i = 0; i < cols; ++i) {
      if (grid[rows][i] != '.') {
        empty_rows[rows] = false;
        empty_cols[i] = false;
      }
    }

    rows++;
  }

  ans = solve(1);

  printf("Part 1: %d\n", ans);
}

void part2(FILE *fp) {
  memset(empty_rows, true, sizeof(empty_rows));
  memset(empty_cols, true, sizeof(empty_cols));
  memset(vis, false, sizeof(vis));

  ll ans = 0;
  rows = 0, cols = 0;

  while (fscanf(fp, "%s\n", grid[rows]) == 1) {
    if (rows == 0)
      cols = strlen(grid[0]);

    for (int i = 0; i < cols; ++i) {
      if (grid[rows][i] != '.') {
        empty_rows[rows] = false;
        empty_cols[i] = false;
      }
    }

    rows++;
  }

  ans = solve(SPACE - 1);

  printf("Part 2: %lld\n", ans);
}

int main(void) {
  FILE *fp = fopen(FILENAME, "r");

  part1(fp);
  rewind(fp);
  part2(fp);

  fclose(fp);
  return 0;
}
