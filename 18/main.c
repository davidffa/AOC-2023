#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

#define CAP 1024
#define ll long long

typedef struct {
  ll x;
  ll y;
} Point;

static Point verts[CAP];
static int verts_sz = 0;

ll calc_area(ll perimeter) {
  ll area = 0;

  for (int i = 0; i < verts_sz; ++i) {
    Point p1 = verts[i];
    Point p2;

    if (i == verts_sz - 1) {
      p2 = verts[0];
    } else {
      p2 = verts[i + 1];
    }

    area += p1.x * p2.y - p1.y * p2.x;
  }

  area /= 2;

  area += perimeter / 2 + 1;

  return area;
}

void part1(FILE *fp) {
  char buf[16];
  char dir;
  int nsteps;

  int x = 0, y = 0;
  int dx, dy;
  int perimeter = 0;

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    char *tok = strtok(buf, " ");
    dir = tok[0];

    if (dir == 'U') {
      dx = 0, dy = -1;
    } else if (dir == 'R') {
      dx = 1, dy = 0;
    } else if (dir == 'D') {
      dx = 0, dy = 1;
    } else if (dir == 'L') {
      dx = -1, dy = 0;
    }

    tok = strtok(NULL, " ");
    nsteps = atoi(tok);

    perimeter += nsteps;

    x += dx * nsteps;
    y += dy * nsteps;

    verts[verts_sz].x = x;
    verts[verts_sz].y = y;
    verts_sz++;
  }

  ll area = calc_area(perimeter);

  printf("Part 1: %lld\n", area);
}

void part2(FILE *fp) {
  verts_sz = 0;

  char buf[16];
  int dir;
  int nsteps;

  ll x = 0, y = 0;
  int dx, dy;
  ll perimeter = 0;

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    char *tok = strtok(buf, "#");
    tok = strtok(NULL, ")");

    int len = strlen(tok);
    dir = tok[len - 1] - '0';

    if (dir == 3) {
      dx = 0, dy = -1;
    } else if (dir == 0) {
      dx = 1, dy = 0;
    } else if (dir == 1) {
      dx = 0, dy = 1;
    } else if (dir == 2) {
      dx = -1, dy = 0;
    }

    tok[len - 1] = '\0';

    nsteps = strtol(tok, (char **)NULL, 16);

    perimeter += nsteps;

    x += dx * nsteps;
    y += dy * nsteps;

    verts[verts_sz].x = x;
    verts[verts_sz].y = y;
    verts_sz++;
  }

  ll area = calc_area(perimeter);

  printf("Part 2: %lld\n", area);
}

int main(void) {
  FILE *fp = fopen(FILENAME, "r");

  part1(fp);
  rewind(fp);
  part2(fp);

  fclose(fp);
  return 0;
}
