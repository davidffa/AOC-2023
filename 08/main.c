#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample3.txt"
#endif

#define ll long long

#define CAP 1024

typedef struct {
  char value[4];
  char left[4];
  char right[4];
} Node;

static Node table[CAP] = {0};
static int table_len = 0;
static char instructions[512] = {0};

void read_input(FILE* fp) {
  fscanf(fp, "%s\n", instructions);
  char buf[32];

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    char* tok = strtok(buf, " = ");

    memcpy(table[table_len].value, tok, 3);

    tok = strtok(NULL, " = (");
    memcpy(table[table_len].left, tok, 3);

    tok = strtok(NULL, " = ");
    memcpy(table[table_len].right, tok, 3);

    table_len++;
  }
}

void part1(void) {
  char curr[4] = "AAA";
  int cursor = 0;
  int ans = 0;

  while (strcmp(curr, "ZZZ") != 0) {
    char dir = instructions[cursor];

    Node* n;

    for (int i = 0; i < table_len; ++i) {
      if (strcmp(table[i].value, curr) == 0) {
        n = &table[i];
        break;
      }
    }

    if (dir == 'L') {
      strcpy(curr, n->left);
    } else {
      strcpy(curr, n->right);
    }

    cursor = (cursor + 1) % strlen(instructions);
    ans++;
  }

  printf("Part 1: %d\n", ans);
}

ll gcd(ll a, ll b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

ll lcm(int* arr, size_t len) {
  assert(len >= 2);
  ll n;

  n = arr[0] * arr[1] / gcd(arr[0], arr[1]);

  for (size_t i = 2; i < len; ++i) {
    n = arr[i] * n / gcd(arr[i], n);
  }

  return n;
}

void part2(void) {
  Node* curr[8] = {NULL};
  int dist[8] = {0};

  int node_len = 0;
  int cursor = 0;
  long long ans = 0;

  for (int i = 0; i < table_len; ++i) {
    if (table[i].value[2] == 'A') {
      curr[node_len++] = &table[i];
    }
  }

  bool finished = false;

  while (!finished) {
    char dir = instructions[cursor];

    for (int i = 0; i < node_len; ++i) {
      if (curr[i]->value[2] == 'Z') continue;
      ++dist[i];

      if (dir == 'L') {
        for (int j = 0; j < table_len; ++j) {
          if (strcmp(table[j].value, curr[i]->left) == 0) {
            curr[i] = &table[j];
            break;
          }
        }
      } else {
        for (int j = 0; j < table_len; ++j) {
          if (strcmp(table[j].value, curr[i]->right) == 0) {
            curr[i] = &table[j];
            break;
          }
        }
      }
    }

    finished = true;
    for (int i = 0; i < node_len; ++i) {
      if (curr[i]->value[2] != 'Z') {
        finished = false;
        break;
      }
    }

    cursor = (cursor + 1) % strlen(instructions);
  }

  ans = lcm(dist, node_len);

  printf("Part 2: %lld\n", ans);
}

int main(void) {
  FILE* fp = fopen(FILENAME, "r");

  read_input(fp);
  part1();
  part2();

  fclose(fp);
}
