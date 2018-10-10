#include <stdio.h>
#include <deck.h>
#include <player.h>

int main(int args, char* argv[]) 
{
int play = 1; //1 true, 0 false
int turn = 1; //1 true, 0 false
struct deck Deck;
struct player player, comp;
char inputRank;
while(play==1){
//Start game
//Shuffle
  Deck.shuffle();
//Deal cards
  Deck.deal_player_cards(&player);
  Deck.deal_player_cards(&comp);
//Player 1 starts
  while(turn==1){
    player.display_hand(&player);
    player.display_book(&player,1);
    comp.display_book(&comp,2);
    inputRank = player.user_play(&player);
  }
//Display player 1's hand
//Display player 1's book
//Display player 2's book

//Prompt player 1 to enter a rank

//Check player 2's hand to see if they have that rank
//transfer card function

//while loop for while player 1 is getting cards, prompt for another turn
//if false, player 1 fishes
//each time get a card, check for book

//player 2's turn -> goes through same cycle, want generic loop

//keep looping until 7 books

//at end output winner and scores(num of books)
//ask if want to play again, if yes, start loop again, if no, exit
}
}
