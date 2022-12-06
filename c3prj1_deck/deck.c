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

void add_card_to(deck_t * deck, card_t c) {
  card_t *card = malloc(sizeof(*card));
  card->value = c.value;
  card->suit = c.suit;
  deck->cards = realloc(deck->cards, (deck->n_cards + 1)*sizeof(*(deck->cards)));
  deck->cards[deck->n_cards] = &card;
  deck->n_cards++;
}

card_t * add_empty_card(deck_t * deck) {
  card_t c = {.value=0,.suit=0};
  add_card_to(deck, c);
  return deck->cards[deck->n_cards-1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
  deck_t *ans = malloc(sizeof(*ans));
  ans->cards = NULL;
  ans->n_cards = 0;
  for (int i=0; i < 52; i++) {
    card_t c = card_from_num(i);
    if (deck_contains(excluded_cards, c)) {
      continue;
    }
    add_card_to(ans, c);
  }
  return ans;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t *exclu = malloc(sizeof(*exclu));
  exclu->cards = NULL;
  exclu->n_cards = 0;
  for (int i=0; i < n_hands; i++) {
    card_t **cards = hands[i]->cards;
    size_t len = hands[i]->n_cards;
    for (int j=0; j < len; j++) {
      add_card_to(exclu, *cards[j]);
    }
  }
  deck_t *ans = make_deck_exclude(exclu);
  free(exclu);  // Observe
  return ans;
}

void free_deck(deck_t * deck) {
  for (int i=0, l=deck->n_cards; i < l; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}
