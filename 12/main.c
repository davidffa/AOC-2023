#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

#define CAP 32 * 5

#define ll long long

static char buf[CAP];
static int len = 0;
static int damaged[32];
static int damaged_len = 0;

static ll mem[CAP][CAP][CAP];

ll count(int spring_cur, int damaged_cur, int dmg_cnt) {
  if (mem[spring_cur][damaged_cur][dmg_cnt] != -1)
    return mem[spring_cur][damaged_cur][dmg_cnt];

  if (spring_cur == len) {
    if (damaged_cur == damaged_len && dmg_cnt == 0) return 1;
    if (damaged_cur == damaged_len - 1 && damaged[damaged_cur] == dmg_cnt) return 1;
    return 0;
  }

  ll value = 0;

  if (buf[spring_cur] == '#') {
    value = count(spring_cur + 1, damaged_cur, dmg_cnt + 1);
  } else if (buf[spring_cur] == '.') {
    if (dmg_cnt == 0) {
      value = count(spring_cur + 1, damaged_cur, 0);
    }

    if (damaged_cur < damaged_len && damaged[damaged_cur] == dmg_cnt) {
      value = count(spring_cur + 1, damaged_cur + 1, 0);
    }
  } else if (buf[spring_cur] == '?') {
    value += count(spring_cur + 1, damaged_cur, dmg_cnt + 1);

    if (dmg_cnt == 0) {
      value += count(spring_cur + 1, damaged_cur, 0);
    }

    if (damaged_cur < damaged_len && damaged[damaged_cur] == dmg_cnt) {
      value += count(spring_cur + 1, damaged_cur + 1, 0);
    }
  }

  mem[spring_cur][damaged_cur][dmg_cnt] = value;

  return value;
}

void part1(FILE *fp) {
  int ans = 0;

  char dmg_buf[CAP];

  while (fscanf(fp, "%s %s\n", buf, dmg_buf) == 2) {
    memset(mem, -1, sizeof(mem));
    damaged_len = 0;
    len = strlen(buf);

    char *tok = strtok(dmg_buf, ",");
    damaged[damaged_len++] = atoi(tok);

    while ((tok = strtok(NULL, ",")) != NULL) {
      damaged[damaged_len++] = atoi(tok);
    }

    ans += count(0, 0, 0);
  }

  printf("Part 1: %d\n", ans);
}

void part2(FILE *fp) {
  memset(mem, -1, sizeof(mem));
  ll ans = 0;

  char dmg_buf[CAP];

  while (fscanf(fp, "%s %s\n", buf, dmg_buf) == 2) {
    memset(mem, -1, sizeof(mem));
    damaged_len = 0;
    len = strlen(buf);

    char *tok = strtok(dmg_buf, ",");
    damaged[damaged_len++] = atoi(tok);

    while ((tok = strtok(NULL, ",")) != NULL) {
      damaged[damaged_len++] = atoi(tok);
    }

    buf[len++] = '?';

    for (int i = 0; i < 5; ++i) {
      memcpy(buf + i * len, buf, len);
      memcpy(damaged + i * damaged_len, damaged, damaged_len * sizeof(int));
    }

    len *= 5;
    --len;
    damaged_len *= 5;

    ans += count(0, 0, 0);
  }

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
