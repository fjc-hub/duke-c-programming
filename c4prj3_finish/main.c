#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

int win_hand(deck_t ** deck_array,int n_hands){
  int w[n_hands+1];
  for(int u=0;u<n_hands+1;u++) w[u]=0;  
  int v=0;
  for(int i =0;i<n_hands-1;i++){
    for (int j=i+1;j<n_hands;j++){
      // print_hand(deck_array[i]);
      //            print_hand(deck_array[j]);
      // printf("\n");
      v=compare_hands(deck_array[i],deck_array[j]);
      if(v>0) w[i]++;
      else if (v<0) w[j]++;
      else w[n_hands]++;  
    }
  }
  unsigned largest= 0;
  for(int x=0;x<n_hands+1;x++){
    if(w[x] > w[largest])largest=x;
  }
   int count=0;  
    if(w[n_hands]>0){ 
      for(int x=0;x<n_hands+1;x++){
      	if(w[x] == w[largest]) count++;
	 }
     }
    if(count>1) return n_hands;
  return  largest;  
}

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
    int c =win_hand(decks, n_hands);
    winCnts[c]++;
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
