#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

int isEqualCard(card_t c1, card_t c2) {
  if (c1.suit == c2.suit && c1.value == c2.value) {
    return 1;
  }
  return 0;
}

void print_hand(deck_t * hand){
  for (int i=0; i < hand->n_cards; i++) {
    print_card(*((hand->cards)[i]));
    printf("%c", ' ');
  }
}

int deck_contains(deck_t * d, card_t c) {
  for (int i=0; i < d->n_cards; i++) {
    if ((isEqualCard(c, *((d->cards)[i]))) == 1) {
      return 1;
    }
    
  }
  return 0;
}

void shuffle(deck_t * d){
  int remain = d->n_cards;
  int limit = d->n_cards - 1;
  for (int i=0; i < limit; i++) {
    // should not need to use the srand() function
    int idx = rand() % remain + i;  
    // swap idx's deck_t and i's deck_t
    card_t * tmp = (d->cards)[i];
    (d->cards)[i] = (d->cards)[idx];
    (d->cards)[idx] = tmp;
    remain--;
  }
}

void assert_full_deck(deck_t * d) {
  for (int i=0; i < d->n_cards; i++) { 
    assert_card_valid(*((d->cards)[i]));
    for (int j=0; j < d->n_cards; j++) {
      if (i == j) {
        continue;
      }
      assert(!(isEqualCard(*((d->cards)[i]), *((d->cards)[j]))));
    }
  } 
}

