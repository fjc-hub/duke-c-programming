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
  FILE *f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("open file error in main\n");
    return EXIT_FAILURE;
  }
  size_t n_hands = 0;
  future_cards_t *fc = malloc(sizeof(*fc));
  fc->decks = NULL;
  fc->n_decks = 0;
  deck_t **decks = read_input(f, &n_hands, fc);
  deck_t *remain = build_remaining_deck(decks, n_hands);
  int num_trials = 10000;
  if (argc ==3) {
    num_trials = atoi(argv[2]);
  }
  int winCnts[n_hands+1];
  for (int i=0; i <= n_hands; i++) {
    winCnts[i] = 0;
  }
  // Monte Carlo trials
  for (int mc=0; mc < num_trials; mc++) {
    shuffle(remain);
    future_cards_from_deck(remain, fc);
    //
    unsigned cnts[n_hands];
    for (int i=0; i < n_hands; i++) {
      cnts[i] = 0;
    }
    for(int i=0; i < n_hands; i++){
      for (int j=i+1; j < n_hands; j++){
        int cmp = compare_hands(decks[i], decks[j]);
        if(cmp > 0) {
          cnts[i]++;
        } else if (cmp < 0) {
          cnts[j]++;
        } 
      }
    }
    int tie = 0;
    unsigned max = 0;
    for (int i=1; i < n_hands; i++) {
      if (cnts[max] < cnts[i]) {
        max = i;
        tie = 0;
      } else if (cnts[max] == cnts[i]) {
        tie = 1;
      }
    }
    if (tie == 0) {
      winCnts[max]++;
    } else {
      winCnts[n_hands]++;
    }
  }
  // print
  for (size_t i=0; i < n_hands; i++) {
    printf("Hand %zu won %u / %u times (%.2f%%)\n", i, winCnts[i], num_trials, (((float)winCnts[i])/num_trials)*100);
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
