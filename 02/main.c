#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

#define CAP 256

#define MAX(a, b) (a > b) ? a : b

int get_max_amount(char* color) {
  if (strcmp(color, "red") == 0) {
    return 12;
  }

  if (strcmp(color, "green") == 0) {
    return 13;
  }

  if (strcmp(color, "blue") == 0) {
    return 14;
  }

  assert(0 && "Unreachable");
}

void part1(FILE* fp) {
  char buf[CAP], game[64], color[8];
  char *last_game, *last_cube;
  int game_n, cube_amt, sum = 0;
  bool cont;

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    cont = true;
    char* tok = strtok_r(buf, ":", &last_game);

    sscanf(tok, "Game %d", &game_n);

    while (cont) {
      tok = strtok_r(NULL, ";", &last_game);
      if (tok == NULL) break;

      strcpy(game, tok);

      char* cube = strtok_r(game, ",", &last_cube);

      while (cube != NULL) {
        sscanf(cube, "%d %s", &cube_amt, color);

        int max_amt = get_max_amount(color);

        if (cube_amt > max_amt) {
          cont = false;
        }

        cube = strtok_r(NULL, ",", &last_cube);
      }
    }

    if (cont) {
      sum += game_n;
    }
  }

  printf("Part 1: %d\n", sum);
}

void part2(FILE* fp) {
  char buf[CAP], game[64], color[8];
  char *last_game, *last_cube;
  int cube_amt, sum = 0;
  int r, g, b;

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    r = 0, g = 0, b = 0;
    char* tok = strtok_r(buf, ":", &last_game);

    while (true) {
      tok = strtok_r(NULL, ";", &last_game);
      if (tok == NULL) break;

      strcpy(game, tok);

      char* cube = strtok_r(game, ",", &last_cube);

      while (cube != NULL) {
        sscanf(cube, "%d %s", &cube_amt, color);

        if (strcmp(color, "red") == 0) {
          r = MAX(r, cube_amt);
        } else if (strcmp(color, "green") == 0) {
          g = MAX(g, cube_amt);
        } else if (strcmp(color, "blue") == 0) {
          b = MAX(b, cube_amt);
        } else {
          assert(0 && "Unreachable");
        }

        cube = strtok_r(NULL, ",", &last_cube);
      }
    }
    sum += r * g * b;
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
