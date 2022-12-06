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
  //check arguments
  if (argc < 2 ){
    fprintf(stderr, "not enough number of arguments\n");
    return EXIT_FAILURE ;
  }
  //Open the input file and read the hands in it
  FILE* f=fopen(argv[1],"r");
  if(f == NULL) {
    fprintf(stderr, "not valid  input file\n");
    return EXIT_FAILURE ;
  }
  deck_t ** deck_array=NULL;
  size_t n_hands =0 ;
  future_cards_t * fc=malloc(sizeof(*fc));
  fc->decks=NULL;
  fc->n_decks=0;
  deck_array=read_input(f,&n_hands,fc);
  //Create a deck with the remaining cards
  deck_t* sh=build_remaining_deck(deck_array, n_hands);
  int win_array[n_hands+1];
   for(int u=0;u<n_hands+1;u++) win_array[u]=0;
  // Do each Monte Carlo trial (repeat num_trials times)
  int num_trials = 10000;
  if (argc ==3) num_trials=atoi(argv[2]);
  for(int i=0;i<num_trials;i++){
    //Shuffle the deck of remaining cards
    shuffle(sh);
    //Assign unknown cards from the shuffled deck
    future_cards_from_deck(sh,fc);
    //Use compare_hands (from Course 3)
    int c =win_hand(deck_array,n_hands);
    win_array[c]++;
  }
  //you just need to print your results
  for(size_t j=0;j<n_hands;j++){
    printf("Hand %zu won %u / %u times (%.2f%%)\n",j,win_array[j],num_trials,(((float)win_array[j])/num_trials)*100);
  }
  printf( "And there were %u ties\n",win_array[n_hands]);
  //free any memory you allocated
  for(int x=0;x<n_hands;x++){
    free_deck(deck_array[x]);
  }
  free(deck_array);
  for(int o=fc->n_decks-1 ;o>=0;o--){
    if(fc->decks[o].n_cards != 0) free(fc->decks[o].cards);
  }
  free(fc->decks);
  free(fc);
  free_deck(sh);
 
  if(fclose(f) != 0){
    fprintf(stderr, "close file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
