#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

#define CAP 64

#define ll long long

void part1(FILE* fp) {
  int time[4];
  int dist[4];
  int ans = 1;

  int len = fscanf(fp, "Time: %d %d %d %d\n", &time[0], &time[1], &time[2], &time[3]);
  fscanf(fp, "Distance: %d %d %d %d\n", &dist[0], &dist[1], &dist[2], &dist[3]);

  for (int i = 0; i < len; ++i) {
    int ways = 0;

    int t = time[i];
    int d = dist[i];

    for (int j = 1; j < t; ++j) {
      if ((t - j) * j > d) ways++;
    }

    ans *= (ways > 0) ? ways : 1;
  }

  printf("Part 1: %d\n", ans);
}

void part2(FILE* fp) {
  ll ans = 0;

  char buf[CAP];
  ll time = 0;
  ll dist = 0;

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    char* tok = strtok(buf, " ");

    if (time == 0) {
      while ((tok = strtok(NULL, " ")) != NULL) {
        int len = strlen(tok);
        if (tok[len - 1] == '\n') len--;
        int part = atoi(tok);

        time *= pow(10, len);
        time += part;
      }
    } else {
      while ((tok = strtok(NULL, " ")) != NULL) {
        int len = strlen(tok);
        if (tok[len - 1] == '\n') len--;
        int part = atoi(tok);

        dist *= pow(10, len);
        dist += part;
      }
    }
  }

  for (ll j = 1; j < time; ++j) {
    if ((time - j) * j > dist) ans++;
  }

  printf("Part 2: %lld\n", ans);
}

int main(void) {
  FILE* fp = fopen(FILENAME, "r");
  part1(fp);
  rewind(fp);
  part2(fp);

  fclose(fp);
  return 0;
}
