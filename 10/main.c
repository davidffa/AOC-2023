#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample5.txt"
#endif

#define CAP 256

typedef enum {
  NORTH = 0,
  SOUTH,
  EAST,
  WEST
} Dir;

static int dirs[4][2] = {
    {0, -1},  // North
    {0, 1},   // South
    {1, 0},   // East
    {-1, 0},  // West
};

static char matrix[CAP][CAP];
static bool vis[CAP][CAP];
static char expanded_matrix[CAP * 3][CAP * 3];
static int rows = 0, cols = 0;

bool valid_pipe(int dir, char pipe) {
  if (pipe == '.') return false;

  switch (dir) {
    case NORTH: {
      return (pipe == '|' || pipe == '7' || pipe == 'F');
    } break;
    case SOUTH: {
      return (pipe == '|' || pipe == 'L' || pipe == 'J');
    } break;
    case EAST: {
      return (pipe == '-' || pipe == 'J' || pipe == '7');
    } break;
    case WEST: {
      return (pipe == '-' || pipe == 'L' || pipe == 'F');
    } break;
    default:
      assert(0 && "Unreachable");
  }
}

int next_dir(int old_dir, char pipe) {
  switch (old_dir) {
    case NORTH: {
      // We came from south
      if (pipe == '|')
        return NORTH;
      if (pipe == '7')
        return WEST;
      if (pipe == 'F')
        return EAST;

      assert(0 && "Invalid pipe");
    } break;
    case SOUTH: {
      // We came from north
      if (pipe == '|')
        return SOUTH;
      if (pipe == 'L')
        return EAST;
      if (pipe == 'J')
        return WEST;

      assert(0 && "Invalid pipe");
    } break;
    case EAST: {
      // We came from west
      if (pipe == '-')
        return EAST;
      if (pipe == 'J')
        return NORTH;
      if (pipe == '7')
        return SOUTH;

      assert(0 && "Invalid pipe");
    } break;
    case WEST: {
      // We came from east
      if (pipe == '-')
        return WEST;
      if (pipe == 'L')
        return NORTH;
      if (pipe == 'F')
        return SOUTH;

      assert(0 && "Invalid pipe");
    } break;
    default:
      assert(0 && "Unreachable");
  }

  assert(0 && "Unreachable");
}

// Calculate loop size, starting in 'S'
int loop_size(int r, int c) {
  assert(matrix[r][c] == 'S');

  vis[r][c] = true;

  int sz = 0;
  int r0, c0;
  int new_dir = -1;

  for (int i = 0; i < 4; ++i) {
    c0 = c + dirs[i][0], r0 = r + dirs[i][1];

    if (r0 >= 0 && r0 < rows && c0 >= 0 && c0 < cols && valid_pipe(i, matrix[r0][c0])) {
      sz++;
      new_dir = next_dir(i, matrix[r0][c0]);
      vis[r0][c0] = true;
      break;
    }
  }

  while (1) {
    c0 = c0 + dirs[new_dir][0], r0 = r0 + dirs[new_dir][1];

    if (matrix[r0][c0] == 'S') break;

    vis[r0][c0] = true;
    new_dir = next_dir(new_dir, matrix[r0][c0]);
    sz++;
  }

  return sz;
}

void part1(FILE *fp) {
  int ans;

  rows = 0;
  while (fscanf(fp, "%s\n", matrix[rows]) == 1) {
    rows++;
  }

  cols = strlen(matrix[0]);

  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (matrix[r][c] == 'S') {
        ans = loop_size(r, c) / 2 + 1;
        break;
      }
    }
  }

  printf("Part 1: %d\n", ans);
}

void expand_matrix(void) {
  memset(expanded_matrix, '.', sizeof(expanded_matrix));
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (matrix[r][c] == '|') {
        expanded_matrix[r * 3][c * 3 + 1] = '#';
        expanded_matrix[r * 3 + 1][c * 3 + 1] = '#';
        expanded_matrix[r * 3 + 2][c * 3 + 1] = '#';
      } else if (matrix[r][c] == '-') {
        expanded_matrix[r * 3 + 1][c * 3] = '#';
        expanded_matrix[r * 3 + 1][c * 3 + 1] = '#';
        expanded_matrix[r * 3 + 1][c * 3 + 2] = '#';
      } else if (matrix[r][c] == 'L') {
        expanded_matrix[r * 3][c * 3 + 1] = '#';
        expanded_matrix[r * 3 + 1][c * 3 + 1] = '#';
        expanded_matrix[r * 3 + 1][c * 3 + 2] = '#';
      } else if (matrix[r][c] == 'J') {
        expanded_matrix[r * 3][c * 3 + 1] = '#';
        expanded_matrix[r * 3 + 1][c * 3 + 1] = '#';
        expanded_matrix[r * 3 + 1][c * 3] = '#';
      } else if (matrix[r][c] == '7') {
        expanded_matrix[r * 3 + 1][c * 3] = '#';
        expanded_matrix[r * 3 + 1][c * 3 + 1] = '#';
        expanded_matrix[r * 3 + 2][c * 3 + 1] = '#';
      } else if (matrix[r][c] == 'F') {
        expanded_matrix[r * 3 + 1][c * 3 + 2] = '#';
        expanded_matrix[r * 3 + 1][c * 3 + 1] = '#';
        expanded_matrix[r * 3 + 2][c * 3 + 1] = '#';
      }
    }
  }
}

void remove_outter_space(int r, int c) {
  int r0, c0;
  for (int i = 0; i < 4; ++i) {
    c0 = c + dirs[i][0], r0 = r + dirs[i][1];

    if (c0 >= 0 && c0 < cols * 3 && r0 >= 0 && r0 < rows * 3) {
      if (expanded_matrix[r0][c0] == '.') {
        expanded_matrix[r0][c0] = ' ';
        remove_outter_space(r0, c0);
      }
    }
  }
}

char s_joint(int d1, int d2) {
  if ((d1 == NORTH && d2 == SOUTH) || (d1 == SOUTH && d2 == NORTH))
    return '|';
  if ((d1 == EAST && d2 == WEST) || (d1 == WEST && d2 == EAST))
    return '-';
  if ((d1 == NORTH && d2 == EAST) || (d1 == EAST && d2 == NORTH))
    return 'L';
  if ((d1 == NORTH && d2 == WEST) || (d1 == WEST && d2 == NORTH))
    return 'J';
  if ((d1 == SOUTH && d2 == WEST) || (d1 == WEST && d2 == SOUTH))
    return '7';
  if ((d1 == EAST && d2 == SOUTH) || (d1 == SOUTH && d2 == EAST))
    return 'F';

  assert(0 && "Invalid S ?");
}

void part2(FILE *fp) {
  memset(vis, false, sizeof(vis));
  int ans = 0;

  rows = 0;
  while (fscanf(fp, "%s\n", matrix[rows]) == 1) {
    rows++;
  }

  cols = strlen(matrix[0]);

  int c0, r0;
  int sdirs[2];
  int sdirs_len = 0;

  int s_row, s_col;

  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (matrix[r][c] == 'S') {
        loop_size(r, c);
        s_row = r, s_col = c;
        for (int i = 0; i < 4; ++i) {
          c0 = c + dirs[i][0], r0 = r + dirs[i][1];

          if (r0 >= 0 && r0 < rows && c0 >= 0 && c0 < cols && valid_pipe(i, matrix[r0][c0])) {
            sdirs[sdirs_len++] = i;
          }
        }
      }
    }
  }

  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (!vis[r][c]) matrix[r][c] = '.';
    }
  }

  assert(sdirs_len == 2);
  matrix[s_row][s_col] = s_joint(sdirs[0], sdirs[1]);

  expand_matrix();
  remove_outter_space(0, 0);

  for (int r = 1; r < rows * 3 - 3; r += 3) {
    for (int c = 1; c < cols * 3 - 3; c += 3) {
      if (
          expanded_matrix[r - 1][c - 1] == '.' &&
          expanded_matrix[r - 1][c] == '.' &&
          expanded_matrix[r - 1][c + 1] == '.' &&
          expanded_matrix[r][c - 1] == '.' &&
          expanded_matrix[r][c] == '.' &&
          expanded_matrix[r][c + 1] == '.' &&
          expanded_matrix[r + 1][c - 1] == '.' &&
          expanded_matrix[r + 1][c] == '.' &&
          expanded_matrix[r + 1][c + 1] == '.') {
        expanded_matrix[r - 1][c - 1] = 'I';
        expanded_matrix[r - 1][c] = 'I';
        expanded_matrix[r - 1][c + 1] = 'I';
        expanded_matrix[r][c - 1] = 'I';
        expanded_matrix[r][c] = 'I';
        expanded_matrix[r][c + 1] = 'I';
        expanded_matrix[r + 1][c - 1] = 'I';
        expanded_matrix[r + 1][c] = 'I';
        expanded_matrix[r + 1][c + 1] = 'I';
        ans++;
      }
    }
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
