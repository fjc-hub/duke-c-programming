#include <stdio.h>
#include "cards.h"

int main(void) {
    
    const char* cnm = ranking_to_string(THREE_OF_A_KIND);
    printf("%s\n", cnm); // "THREE OF A KIND"

    card_t t1 = {13, CLUBS};
    assert_card_valid(t1);
    char c1 = value_letter(t1); // separate from printf
    char c2 = suit_letter(t1);  // because function call'priority may < format
    printf("%c %c\n", c1, c2); // "K c"

    card_t t2 = {14, DIAMONDS};
    assert_card_valid(t2);
    print_card(t2); // "Ad"
    printf("\n");

    card_t t3 = card_from_letters('A', 's');
    assert_card_valid(t3);
    print_card(t3); // "As"
    printf("\n");

    card_t t0 = {0, SPADES};
    assert_card_valid(t0);
}
