#include <stdlib.h>
#include <stdio.h>
#include "input.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
    int cnt = 0;
    deck_t *ans = malloc(sizeof(*ans));
    ans->cards = NULL;
    ans->n_cards = 0;
    for (int i=0, len=strlen(str); i < len; cnt++) {
        if (str[i] == ' ') {
            continue;
        }
        assert(i+1 < len);
        char v = str[i++], s = str[i++];
        assert(i == len || str[i] == ' ');
        if (v == '?') {
            assert(isdigit(s));
            card_t *ptr = add_empty_card(ans);
            add_future_card(fc, s-'0', ptr);
        } else {
            card_t card = card_from_letters(v, s);
            card_t *tmp = malloc(sizeof(*tmp));
            tmp->value = card.value;
            tmp->suit = card.suit;
            ans->cards = realloc(ans->cards, (ans->n_cards+1)*sizeof(*(ans->cards)));
            ans->cards[ans->n_cards] = tmp;
            ans->n_cards++;
        }
    }
    if (cnt < 5) {
        perror("there are fewer than 5 cards\n");
        exit(-1);
    }
    return ans;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
    *n_hands = 0;
    deck_t **ans = NULL;
    size_t sz = 0;
    char * buf = NULL;
    for (; getline(&buf, &sz, f) >= 0; ) {
        deck_t *deck = hand_from_string(buf, fc);
        ans = realloc(ans, (*n_hands+1)*sizeof(*ans));
        ans[*n_hands] = deck;
        *n_hands = *n_hands + 1;
    }
    free(buf);
    return ans;
}