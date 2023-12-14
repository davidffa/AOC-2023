#include <assert.h>
#include <stdio.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

#define CYCLES 1000000000
#define CAP 128

typedef enum {
  NORTH = 0,
  SOUTH,
  EAST,
  WEST,
} Dir;

static char grid[CAP][CAP];
static char grids[200][CAP][CAP];
static int grids_len = 1;
static int rows = 0, cols = 0;

void read_input(FILE *fp) {
  while (fscanf(fp, "%s", grid[rows]) == 1) rows++;

  cols = strlen(grid[0]);

  memcpy(grids[0], grid, sizeof(grid));
}

void rotate(Dir dir) {
  switch (dir) {
    case NORTH: {
      for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
          if (grid[r][c] == 'O') {
            for (int r0 = r - 1; r0 >= 0; --r0) {
              if (grid[r0][c] != '.') break;
              grid[r0][c] = 'O';
              grid[r0 + 1][c] = '.';
            }
          }
        }
      }
    } break;
    case SOUTH: {
      for (int r = rows - 1; r >= 0; --r) {
        for (int c = 0; c < cols; ++c) {
          if (grid[r][c] == 'O') {
            for (int r0 = r + 1; r0 < rows; ++r0) {
              if (grid[r0][c] != '.') break;
              grid[r0][c] = 'O';
              grid[r0 - 1][c] = '.';
            }
          }
        }
      }
    } break;
    case EAST: {
      for (int r = 0; r < rows; ++r) {
        for (int c = cols - 1; c >= 0; --c) {
          if (grid[r][c] == 'O') {
            for (int c0 = c + 1; c0 < cols; ++c0) {
              if (grid[r][c0] != '.') break;
              grid[r][c0] = 'O';
              grid[r][c0 - 1] = '.';
            }
          }
        }
      }
    } break;
    case WEST: {
      for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
          if (grid[r][c] == 'O') {
            for (int c0 = c - 1; c0 >= 0; --c0) {
              if (grid[r][c0] != '.') break;
              grid[r][c0] = 'O';
              grid[r][c0 + 1] = '.';
            }
          }
        }
      }
    } break;
    default:
      assert(0 && "Invalid dir");
  }
}

void part1(void) {
  int ans = 0;

  rotate(NORTH);

  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (grid[r][c] == 'O') {
        ans += rows - r;
      }
    }
  }

  printf("Part 1: %d\n", ans);
}

void part2(void) {
  int ans = 0;

  // Restore original grid from pt1
  memcpy(grid, grids[0], sizeof(grid));

  int cycle_idx = 0;

  for (int i = 0; i < 200; ++i) {
    if (cycle_idx > 0) break;

    rotate(NORTH);
    rotate(WEST);
    rotate(SOUTH);
    rotate(EAST);

    for (int j = 0; j < grids_len; ++j) {
      if (memcmp(grid, grids[j], sizeof(grid)) == 0) {
        cycle_idx = j;
        break;
      }
    }

    if (cycle_idx != 0) break;

    memcpy(grids[grids_len++], grid, sizeof(grid));

    if (grids_len == 200)
      assert(0 && "Cycle not found!");
  }

  int grid_idx = (CYCLES - cycle_idx) % (grids_len - cycle_idx) + cycle_idx;

  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (grids[grid_idx][r][c] == 'O') {
        ans += rows - r;
      }
    }
  }

  printf("Part 2: %d\n", ans);
}

int main(void) {
  FILE *fp = fopen(FILENAME, "r");

  read_input(fp);
  part1();
  part2();

  fclose(fp);
  return 0;
}
