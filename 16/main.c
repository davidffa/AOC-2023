#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

#define CAP 128

#define MAX(a, b) (a > b) ? a : b

typedef enum {
  INVALID = -1,
  UP,
  DOWN,
  LEFT,
  RIGHT
} Dir;

static char grid[CAP][CAP];
static Dir vis[CAP][CAP];

static int rows = 0, cols = 0;

static int dirs[4][2] = {
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0},
};

void read_file(FILE *fp) {
  while (fscanf(fp, "%s", grid[rows]) == 1) {
    rows++;
  }

  cols = strlen(grid[0]);
}

void traverse(int r, int c, Dir d) {
  if (r < 0 || r >= rows || c < 0 || c >= cols)
    return;

  if (vis[r][c] == d)
    return;

  vis[r][c] = d;

  int r0, c0;

  switch (grid[r][c]) {
    case '.': {
      c0 = c + dirs[d][0], r0 = r + dirs[d][1];

      traverse(r0, c0, d);
    } break;
    case '|': {
      if (d == DOWN || d == UP) {
        c0 = c + dirs[d][0], r0 = r + dirs[d][1];
        traverse(r0, c0, d);
        break;
      }

      d = UP;
      c0 = c + dirs[d][0], r0 = r + dirs[d][1];
      traverse(r0, c0, d);
      d = DOWN;
      c0 = c + dirs[d][0], r0 = r + dirs[d][1];
      traverse(r0, c0, d);
    } break;
    case '-': {
      if (d == LEFT || d == RIGHT) {
        c0 = c + dirs[d][0], r0 = r + dirs[d][1];
        traverse(r0, c0, d);
        break;
      }

      d = LEFT;
      c0 = c + dirs[d][0], r0 = r + dirs[d][1];
      traverse(r0, c0, d);
      d = RIGHT;
      c0 = c + dirs[d][0], r0 = r + dirs[d][1];
      traverse(r0, c0, d);
    } break;
    case '\\': {
      if (d == UP)
        d = LEFT;
      else if (d == DOWN)
        d = RIGHT;
      else if (d == LEFT)
        d = UP;
      else if (d == RIGHT)
        d = DOWN;

      c0 = c + dirs[d][0], r0 = r + dirs[d][1];

      traverse(r0, c0, d);
    } break;
    case '/': {
      if (d == UP)
        d = RIGHT;
      else if (d == DOWN)
        d = LEFT;
      else if (d == LEFT)
        d = DOWN;
      else if (d == RIGHT)
        d = UP;

      c0 = c + dirs[d][0], r0 = r + dirs[d][1];

      traverse(r0, c0, d);
    } break;
    default:
      assert(0 && "Unknown symbol");
  }
}

void part1(void) {
  memset(vis, -1, sizeof(vis));

  int ans = 0;

  traverse(0, 0, RIGHT);

  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (vis[r][c] != -1) ++ans;
    }
  }

  printf("Part 1: %d\n", ans);
}

int get_energized(void) {
  int n = 0;

  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (vis[r][c] != -1) ++n;
    }
  }

  return n;
}

void part2(void) {
  int ans = 0, n;

  memset(vis, -1, sizeof(vis));
  traverse(0, 0, RIGHT);
  n = get_energized();
  ans = MAX(ans, n);
  memset(vis, -1, sizeof(vis));
  traverse(0, 0, DOWN);
  n = get_energized();
  ans = MAX(ans, n);

  memset(vis, -1, sizeof(vis));
  traverse(0, cols - 1, LEFT);
  n = get_energized();
  ans = MAX(ans, n);
  memset(vis, -1, sizeof(vis));
  traverse(0, cols - 1, DOWN);
  n = get_energized();
  ans = MAX(ans, n);

  memset(vis, -1, sizeof(vis));
  traverse(rows - 1, 0, UP);
  n = get_energized();
  ans = MAX(ans, n);
  memset(vis, -1, sizeof(vis));
  traverse(rows - 1, 0, RIGHT);
  n = get_energized();
  ans = MAX(ans, n);

  memset(vis, -1, sizeof(vis));
  traverse(rows - 1, cols - 1, LEFT);
  n = get_energized();
  ans = MAX(ans, n);
  memset(vis, -1, sizeof(vis));
  traverse(rows - 1, cols - 1, UP);
  n = get_energized();
  ans = MAX(ans, n);

  for (int r = 1; r < rows - 1; ++r) {
    memset(vis, -1, sizeof(vis));
    traverse(r, 0, RIGHT);
    n = get_energized();
    ans = MAX(ans, n);

    memset(vis, -1, sizeof(vis));
    traverse(r, cols - 1, LEFT);
    n = get_energized();
    ans = MAX(ans, n);
  }

  for (int c = 1; c < cols - 1; ++c) {
    memset(vis, -1, sizeof(vis));
    traverse(0, c, DOWN);
    n = get_energized();
    ans = MAX(ans, n);

    memset(vis, -1, sizeof(vis));
    traverse(rows - 1, c, UP);
    n = get_energized();
    ans = MAX(ans, n);
  }

  printf("Part 2: %d\n", ans);
}

int main(void) {
  FILE *fp = fopen(FILENAME, "r");

  read_file(fp);

  part1();
  part2();

  fclose(fp);
  return 0;
}
