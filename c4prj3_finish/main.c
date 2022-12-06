#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"


int main(int argc, char ** argv) {
  if (argc != 2 || argc != 3) {
    perror("argument number error\n");
    return EXIT_FAILURE;
  }
  size_t n_hands = 0;
  future_cards_t *fc = malloc(sizeof(*fc));
  fc->decks = NULL;
  fc->n_decks = 0;
  FILE *f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("open file error in main\n");
    return EXIT_FAILURE;
  }
  deck_t **decks = read_input(f, &n_hands, fc);
  deck_t *remain = build_remaining_deck(decks, n_hands);
  unsigned winCnts[n_hands+1];
  for (int i=0; i <= n_hands; i++) {
    winCnts[i] = 0;
  }
  size_t num_trials = 10000;
  if (argc == 3) {
    num_trials = atoi(argv[2]);
  }
  // Monte Carlo trials
  for (int i=0; i < num_trials; i++) {
    shuffle(remain);
    future_cards_from_deck(remain, fc);
    int tie = 0;
    int max = 0;
    for (int j=1; j < n_hands; j++) {
      int cmp = compare_hands(decks[max], decks[j]);
      if (cmp < 0) {
        max = i;
      } else if (cmp == 0) {
        tie = 1;
      }
    }
    if (tie == 1) {
      winCnts[n_hands]++;
    } else {
      winCnts[max]++;
    }
  }
  // print
  for (int i=0; i < n_hands; i++) {

  }
  printf("And there were %u ties\n", winCnts[n_hands]);
  // release
  if (fclose(f) != 0) {
    perror("close file error\n");
    return EXIT_FAILURE;
  }
  for (int i=0; i < n_hands; i++) {
    free_deck(decks[i]);
  }
  free(decks);
  free_deck(remain);
  free_deck(fc->decks);
  free(fc);
  return EXIT_SUCCESS;
}
