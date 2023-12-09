#include <stdio.h>

#if 0
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

void part1(FILE *fp) {
  (void)fp;
}

void part2(FILE *fp) {
  (void)fp;
}

int main(void) {
  FILE *fp = fopen(FILENAME, "r");

  part1(fp);
  rewind(fp);
  part2(fp);

  fclose(fp);
  return 0;
}
