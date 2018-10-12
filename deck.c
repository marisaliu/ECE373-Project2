#include "deck.h"
#include <stdio.h>
#define TOTALDECK 52

struct deck deck_instance;

int shuffle() {
  char suit[] = {'C', 'D', 'H', 'S'};
  char rank[] = {'2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K', 'A'};
  struct card newCard;
  int i, random;
  for(i=0; i<TOTALDECK; i++) {
 	newCard.suit = suit[i%4];
	newCard.rank = rank[i%13];
	deck_instance.list[i] = newCard;
  }
  for(i=TOTALDECK-1; i>=0; i--) {
	 random = (rand() % (i+1));
	 newCard = deck_instance.list[i];
	 deck_instance.list[i] = deck_instance.list[random];
	 deck_instance.list[random] = newCard;
	}
  deck_instance.top_card = 0; //cards in deck-1

}

struct hand* initHand() {
  struct hand *newHand;
  newHand = (struct hand*)malloc(sizeof(struct hand));
  return newHand;
}

int deal_player_cards(struct player* target) {
  struct hand *currentHand, *newHand;
  int i;
  currentHand = initHand();
  for(i=0; i<7; i++) {
	 newHand = initHand();
	 if(newHand == NULL) {return -1;}
	 else{
	 currentHand->top = deck_instance.list[deck_instance.top_card++];
	 currentHand->next = newHand;
	 newHand = currentHand;
	 }
  }
  return 0;
}

struct card* next_card() {
  struct card* nextCard = &deck_instance.list[deck_instance.top_card++];
  return nextCard;
}

size_t deck_size() {
  size_t deckSize = (TOTALDECK - deck_instance.top_card) + 1;
  return deckSize;
}
