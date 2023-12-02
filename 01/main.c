#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
#define FILENAME "input2.txt"
#else
#define FILENAME "sample2.txt"
#endif

#define CAP 128
#define N 9

static char* numbers[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

void part1(FILE* fp) {
  char buf[CAP];
  int sum = 0, n;

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    size_t len = strlen(buf);

    for (size_t i = 0; i < len; ++i) {
      if (isdigit(buf[i])) {
        n = 10 * (buf[i] - '0');
        break;
      }
    }

    for (size_t i = len - 1; i >= 0; --i) {
      if (isdigit(buf[i])) {
        n += (buf[i] - '0');
        break;
      }
    }

    sum += n;
  }

  printf("Part 1: %d\n", sum);
}

int number(char* str) {
  size_t len = strlen(str);

  for (int i = 0; i < 9; ++i) {
    char* num = numbers[i];
    size_t len2 = strlen(num);

    if (len2 > len) continue;

    bool ok = true;
    for (size_t j = 0; j < len2 && ok; ++j) {
      ok = str[j] == num[j];
    }

    if (ok) return i + 1;
  }

  return -1;
}

void part2(FILE* fp) {
  char buf[CAP];
  int sum = 0, n, last_n;

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    size_t len = strlen(buf);
    n = 0;

    for (size_t i = 0; i < len; ++i) {
      if (isdigit(buf[i])) {
        if (n == 0)
          n = 10 * (buf[i] - '0');

        last_n = (buf[i] - '0');
      } else {
        int num = number(buf + i);

        if (num != -1) {
          if (n == 0)
            n = 10 * num;

          last_n = num;
        }
      }
    }

    n += last_n;
    sum += n;
  }

  printf("Part 2: %d\n", sum);
}

int main(void) {
  FILE* fp = fopen(FILENAME, "r");

  part1(fp);
  rewind(fp);
  part2(fp);

  fclose(fp);
  return 0;
}
