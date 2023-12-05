#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

#define ll long long

#define CAP 256

void part1(FILE* fp) {
  char buf[CAP];
  ll seeds[32];
  bool changed[32];

  int seeds_len = 0;

  fgets(buf, sizeof(buf), fp);

  char* tok = strtok(buf, " ");

  while ((tok = strtok(NULL, " ")) != NULL) {
    seeds[seeds_len++] = atoll(tok);
  }

  ll src, dst, range;

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    if (buf[0] == '\n') continue;

    if (!isdigit(buf[0])) {
      memset(changed, false, sizeof(changed));
      continue;
    }

    sscanf(buf, "%lld %lld %lld", &dst, &src, &range);

    for (int i = 0; i < seeds_len; ++i) {
      ll seed = seeds[i];

      if (changed[i]) continue;

      if (seed >= src && seed < src + range) {
        seeds[i] = dst + seed - src;
        changed[i] = true;
      }
    }
  }

  ll min_loc = seeds[0];

  for (int i = 1; i < seeds_len; ++i) {
    if (seeds[i] < min_loc)
      min_loc = seeds[i];
  }

  printf("Part 1: %lld\n", min_loc);
}

typedef struct {
  ll min;
  ll max;
  bool changed;
} SeedRange;

typedef struct {
  ll min;
  ll max;
} Range;

void part2(FILE* fp) {
  char buf[CAP];
  SeedRange seeds[128];

  int seeds_len = 0;

  fgets(buf, sizeof(buf), fp);

  char* tok = strtok(buf, " ");

  while ((tok = strtok(NULL, " ")) != NULL) {
    SeedRange s = {0};
    s.min = atoll(tok);
    tok = strtok(NULL, " ");
    s.max = s.min + atoll(tok) - 1;

    seeds[seeds_len++] = s;
  }

  ll range, dst;
  Range src;

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    if (buf[0] == '\n') continue;

    if (!isdigit(buf[0])) {
      for (int i = 0; i < seeds_len; ++i) {
        seeds[i].changed = false;
      }
      continue;
    }

    sscanf(buf, "%lld %lld %lld", &dst, &src.min, &range);

    src.max = src.min + range - 1;

    for (int i = 0; i < seeds_len; ++i) {
      SeedRange* seed = &seeds[i];

      // Seed range is not in almanac line range
      if (seed->changed || seed->max < src.min || seed->min > src.max) continue;

      seed->changed = true;

      if (seed->min >= src.min) {
        // No need to cut the first part of seed range
        seed->min = seed->min - src.min + dst;
      } else {
        SeedRange s = {0};
        s.min = seed->min;
        s.max = src.min - 1;

        seeds[seeds_len++] = s;

        seed->min = dst;
      }

      if (seed->max > src.max) {
        SeedRange s = {0};

        s.min = src.max + 1;
        s.max = seed->max;

        seeds[seeds_len++] = s;
        seed->max = dst + range - 1;
      } else
        seed->max = dst + range - 1 - src.max + seed->max;
    }
  }

  ll min_loc = seeds[0].min;

  for (int i = 1; i < seeds_len; ++i) {
    if (seeds[i].min < min_loc)
      min_loc = seeds[i].min;
  }

  printf("Part 2: %lld\n", min_loc);
}

int main(void) {
  FILE* fp = fopen(FILENAME, "r");

  part1(fp);
  rewind(fp);
  part2(fp);

  fclose(fp);
  return 0;
}
