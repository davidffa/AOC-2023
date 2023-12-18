#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

#define CAP 256

typedef struct {
  uint8_t heat;
  uint32_t dist;
  int dir[2];
  int r;
  int c;
} Vertex;

typedef struct {
  Vertex* items[CAP * 64];
  int size;
} PriorityQueue;

PriorityQueue* pq_create(void) {
  PriorityQueue* pq = malloc(sizeof(PriorityQueue));
  pq->size = 0;
  return pq;
}

void pq_insert(PriorityQueue* pq, Vertex* item) {
  int i = 0;

  for (; i < pq->size; ++i) {
    if (item->dist > pq->items[i]->dist) {
      for (int j = pq->size; j > i; --j) {
        pq->items[j] = pq->items[j - 1];
      }
      break;
    }
  }

  pq->items[i] = item;
  pq->size++;
}

Vertex* pq_pop(PriorityQueue* pq) {
  return pq->items[--pq->size];
}

Vertex* clone_vertex(Vertex* v) {
  Vertex* v2 = malloc(sizeof(Vertex));

  v2->c = v->c;
  v2->r = v->r;
  v2->dir[0] = v->dir[0];
  v2->dir[1] = v->dir[1];
  v2->heat = v->heat;
  v2->dist = v->dist;

  return v2;
}

static int dir[4][2] = {
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0},
};

static Vertex grid[CAP][CAP];
static uint32_t dists[CAP][CAP][4];
static int rows = 0, cols = 0;

void read_input(FILE* fp) {
  char buf[CAP];

  while (fscanf(fp, "%s", buf) == 1) {
    cols = strlen(buf);

    for (int i = 0; i < cols; ++i) {
      grid[rows][i].heat = buf[i] - '0';
      grid[rows][i].dist = UINT32_MAX;
      grid[rows][i].c = i;
      grid[rows][i].r = rows;
    }

    rows++;
  }
}

int dijkstra(int minsteps, int maxsteps) {
  memset(dists, UINT32_MAX, sizeof(dists));
  grid[0][0].dist = 0;

  int dr, dc, dr1, dc1, r, c;

  PriorityQueue* pq = pq_create();

  pq_insert(pq, clone_vertex(&grid[0][0]));

  while (pq->size > 0) {
    Vertex* v = pq_pop(pq);

    if (v->r == rows - 1 && v->c == cols - 1) {
      free(pq);
      return v->dist;
    }

    dc = v->dir[0], dr = v->dir[1];
    for (int i = 0; i < 4; ++i) {
      dc1 = dir[i][0];
      dr1 = dir[i][1];

      if ((dc == dc1 && dr == dr1) || (dc == -dc1 && dr == -dr1)) continue;

      uint32_t dist = v->dist;
      for (int j = 1; j <= maxsteps; ++j) {
        c = v->c + dc1 * j;
        r = v->r + dr1 * j;

        if (c < 0 || c == cols || r < 0 || r == rows) continue;

        dist += grid[r][c].heat;
        if (j < minsteps) continue;
        if (dist < dists[r][c][i]) {
          Vertex* v2 = clone_vertex(&grid[r][c]);

          v2->dist = dist;
          v2->dir[0] = dc1;
          v2->dir[1] = dr1;

          pq_insert(pq, v2);

          dists[r][c][i] = dist;
        }
      }
    }

    free(v);
  }

  assert(0 && "Unreachable");
}

void part1(void) {
  uint32_t dist = dijkstra(1, 3);

  printf("Part 1: %u\n", dist);
}

void part2(void) {
  uint32_t dist = dijkstra(4, 10);

  printf("Part 2: %u\n", dist);
}

int main(void) {
  FILE* fp = fopen(FILENAME, "r");
  read_input(fp);
  fclose(fp);

  part1();
  part2();

  return 0;
}
