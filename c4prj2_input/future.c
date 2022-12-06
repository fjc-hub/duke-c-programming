#include <stdlib.h>
#include <stdio.h>
#include "future.h"

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
    for (; fc->n_decks <= index; ) {
        fc->decks = realloc(fc->decks, (fc->n_decks+1)*sizeof(*(fc->decks)));
        fc->decks[fc->n_decks].cards = NULL;
        fc->decks[fc->n_decks].n_cards = 0;
        fc->n_decks++;
    }
    // error behavior, result from ptr can't shared by multiple hands
    // add_card_to(&(fc->decks[index]), *ptr);
    // free(ptr); // add_card_to will malloc new card_t *
    // 
    fc->decks[index].cards = realloc(fc->decks[index].cards, (fc->decks[index].n_cards+1)*sizeof(*(fc->decks[index].cards)));
    fc->decks[index].cards[fc->decks[index].n_cards] = ptr;
    fc->decks[index].n_cards++;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
    if (deck->n_cards < fc->n_decks) {
        perror("card in deck can't fill in all placeholders\n");
        return ;
    }
    for (int i=0; i < fc->n_decks; i++) {
        card_t **t = fc->decks[i].cards;
        size_t l = fc->decks[i].n_cards;
        if (fc->decks[i].n_cards == 0) {
            continue;
        }
        for (int j=0; j < l; i++) {
            t[j]->value = deck->cards[i]->value;
            t[j]->suit = deck->cards[i]->suit;
        }
    }
}