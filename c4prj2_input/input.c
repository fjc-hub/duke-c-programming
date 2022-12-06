#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
#include "cards.h"
#include "future.h"
deck_t * hand_from_string(const char * str, future_cards_t * fc){
  deck_t* deck=malloc(sizeof(*deck));
  deck->cards = NULL;
  deck->n_cards=0;
  for(int i=0;i<strlen(str);i++){
    if((str[i] == '\n')||(str[i] == ' '))continue;
    else{
      if(str[i] == '?'){
        i++;
        char num[strlen(str)];
        int n=0;
        while(!((str[i] == '\n')||(str[i] == ' '))) {
          num[n]=str[i];
          i++;n++;}
        num[n]='\0';
        add_future_card(fc,atoi(num),add_empty_card(deck)) ;

      }
      else{
        card_t x = card_from_letters(str[i],str[i+1]);
        add_card_to(deck,x);
        i++;}
    }
  }
  if (deck->n_cards < 5 ){
    return NULL;
    fprintf(stderr,"asas");}
  return deck;
}
deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){
  deck_t **arr=NULL;
  size_t n_hand=0;
  char *line=NULL;
  size_t sz=0;
  while(getline(&line,&sz,f)>=0){
    arr=realloc(arr,(n_hand+1)*sizeof(*arr));
    deck_t*deck=hand_from_string(line,fc);
    if (deck == NULL)continue;
    arr[n_hand]=deck;
    n_hand ++;
  }
  free(line);
  *n_hands=n_hand;
  return arr;
}
