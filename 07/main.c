#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#if 1
#define FILENAME "input.txt"
#else
#define FILENAME "sample2.txt"
#endif

#define CAP 1024

typedef enum {
  HighCard,
  OnePair,
  TwoPair,
  ThreeKind,
  FullHouse,
  FourKind,
  FiveKind
} HandType;

typedef struct {
  char cards[5];
  int bid;
  HandType type;
} Hand;

static int part = 1;

int sym_to_digit(char sym) {
  if (isdigit(sym)) return sym - '0';

  switch (sym) {
    case 'A':
      return 14;
    case 'K':
      return 13;
    case 'Q':
      return 12;
    case 'J': {
      if (part == 2)
        return 1;
      else
        return 11;
    }
    case 'T':
      return 10;
  }

  assert(0 && "Unknown card symbol!");
}

int comparator(const void* p1, const void* p2) {
  Hand* h1 = (Hand*)p1;
  Hand* h2 = (Hand*)p2;

  if (h1->type != h2->type) {
    return h1->type - h2->type;
  }

  for (int i = 0; i < 5; ++i) {
    if (h1->cards[i] == h2->cards[i]) continue;

    int sym1 = sym_to_digit(h1->cards[i]);
    int sym2 = sym_to_digit(h2->cards[i]);

    return sym1 - sym2;
  }

  assert(0 && "Same card deck!");
}

int comparator_int(const void* p1, const void* p2) {
  int* n1 = (int*)p1;
  int* n2 = (int*)p2;

  return (*n2) - (*n1);
}

void set_handtype(Hand* h) {
  int card_map[13] = {0};
  int jokers = 0;

  if (part == 1) {
    for (int i = 0; i < 5; ++i) {
      char sym = h->cards[i];

      ++card_map[sym_to_digit(sym) - 2];
    }
  } else if (part == 2) {
    for (int i = 0; i < 5; ++i) {
      char sym = h->cards[i];

      if (sym == 'J') {
        jokers++;
        continue;
      }

      ++card_map[sym_to_digit(sym) - 2];
    }
  } else {
    assert(0 && "Unknown part");
  }

  qsort(card_map, 13, sizeof(int), comparator_int);

  card_map[0] += jokers;

  switch (card_map[0]) {
    case 1: {
      h->type = HighCard;
    } break;
    case 2: {
      if (card_map[1] == 2)
        h->type = TwoPair;
      else
        h->type = OnePair;
    } break;
    case 3: {
      if (card_map[1] == 2)
        h->type = FullHouse;
      else
        h->type = ThreeKind;
    } break;
    case 4: {
      h->type = FourKind;
    } break;
    case 5: {
      h->type = FiveKind;
    } break;
    default: {
      assert(0 && "Unreachable");
    }
  }
}

void part1(FILE* fp) {
  Hand hands[CAP];
  int hands_len = 0;

  while (fscanf(fp, "%s %d\n", hands[hands_len].cards, &hands[hands_len].bid) == 2) {
    set_handtype(&hands[hands_len]);
    hands_len++;
  }

  qsort(hands, hands_len, sizeof(Hand), comparator);

  int ans = 0;

  for (int i = 0; i < hands_len; ++i) {
    ans += hands[i].bid * (i + 1);
  }

  printf("Part 1: %d\n", ans);
}

void part2(FILE* fp) {
  Hand hands[CAP];
  int hands_len = 0;

  while (fscanf(fp, "%s %d\n", hands[hands_len].cards, &hands[hands_len].bid) == 2) {
    set_handtype(&hands[hands_len]);
    hands_len++;
  }

  qsort(hands, hands_len, sizeof(Hand), comparator);

  int ans = 0;

  for (int i = 0; i < hands_len; ++i) {
    ans += hands[i].bid * (i + 1);
  }

  printf("Part 2: %d\n", ans);
}

int main(void) {
  FILE* fp = fopen(FILENAME, "r");

  part = 1;
  part1(fp);
  rewind(fp);
  part = 2;
  part2(fp);

  fclose(fp);
  return 0;
}
