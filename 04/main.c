#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

#define CAP 128
#define N 32
#define MXCARDS 200

bool contains(int* arr, int len, int n) {
  for (int i = 0; i < len; ++i) {
    if (arr[i] == n) return true;
  }

  return false;
}

void part1(FILE* fp) {
  char buf[CAP];
  int winning[N];
  int nums[N];

  int w_len = 0, n_len = 0;
  int sum = 0, points = 1;

  char *last_nums, *last_n;

  char arr[N];

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    w_len = 0, n_len = 0;
    points = 0;

    char* tok = strtok_r(buf, ":", &last_nums);

    tok = strtok_r(NULL, "|", &last_nums);

    strcpy(arr, tok);

    char* num_tok = strtok_r(arr, " ", &last_n);

    while (num_tok != NULL) {
      winning[w_len++] = atoi(num_tok);
      num_tok = strtok_r(NULL, " ", &last_n);
    }

    tok = strtok_r(NULL, "|", &last_nums);

    num_tok = strtok_r(tok, " ", &last_n);

    while (num_tok != NULL) {
      nums[n_len++] = atoi(num_tok);
      num_tok = strtok_r(NULL, " ", &last_n);
    }

    for (int i = 0; i < n_len; ++i) {
      if (contains(winning, w_len, nums[i])) {
        if (points == 0)
          points = 1;
        else
          points *= 2;
      }
    }
    sum += points;
  }

  printf("Part 1: %d\n", sum);
}

void part2(FILE* fp) {
  char buf[CAP];
  int winning[N];
  int nums[N];

  int w_len = 0, n_len = 0;
  int sum = 0;
  int card_n = 1;

  char *last_nums, *last_n;

  int cards[MXCARDS + 1] = {0};  // 1 indexed
  char arr[N];

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    ++cards[card_n];
    w_len = 0, n_len = 0;

    char* tok = strtok_r(buf, ":", &last_nums);

    tok = strtok_r(NULL, "|", &last_nums);

    strcpy(arr, tok);

    char* num_tok = strtok_r(arr, " ", &last_n);

    while (num_tok != NULL) {
      winning[w_len++] = atoi(num_tok);
      num_tok = strtok_r(NULL, " ", &last_n);
    }

    tok = strtok_r(NULL, "|", &last_nums);

    num_tok = strtok_r(tok, " ", &last_n);

    while (num_tok != NULL) {
      nums[n_len++] = atoi(num_tok);
      num_tok = strtok_r(NULL, " ", &last_n);
    }

    int matches = 1;

    for (int i = 0; i < n_len; ++i) {
      if (contains(winning, w_len, nums[i])) {
        cards[card_n + matches++] += cards[card_n];
      }
    }

    card_n++;
  }

  for (int i = 1; i <= MXCARDS; ++i) {
    sum += cards[i];
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
