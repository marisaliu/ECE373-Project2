#include <stdio.h>
#include "deck.h"
//
int main(int args, char* argv[]) 
{
char bookAdded;
char inputRank;
int transferCards;
int play = 1; //1 true, 0 false
int turn = 1; //1 true, 0 false
int win = 0;  //1 true, 0 false
int playAgain = 0;
struct card* nextCard;
struct deck Deck;
struct player player, comp;
while(play==1){
//Start game
//Shuffle
  Deck.shuffle();
//Deal cards
  Deck.deal_player_cards(&player);
  Deck.deal_player_cards(&comp);
  while(win == 0){
//Player 1 starts
    while((turn==1) && (win == 0){
      player.display_hand(&player);       //Display player 1's hand
      player.display_book(&player,1);     //Display player 1's book 
      comp.display_book(&comp,2);         //Display player 1's book
      inputRank = player.user_play(&player); //Prompt player 1 to enter a rank
      transferCards = comp.search(&player, inputRank); //Check player 2's hand to see if they have that rank
      if(transferCards == 1){           //If they have the rank transfer the cards
        player.transfer_cards(&player, &comp, inputRank);
        bookAdded = player.check_add_book(&player, inputRank);
        if(bookAdded != 0){
          win = player.game.over(&player);
          if(win == 1) break;
	}
	printf("\nPlayer 1 gets another turn");
      }
      else{                            //If they dont have the card exit the loop and switch to player 2's turn
        printf("Player 2 has no %c's", inputRank);
        card* nextCard = Deck.next_card();  //Draw a card from deck
        printf("\nGo Fish, Player 1 draws %c%c", nextCard->rank, nextCard->suit);
        bookAdded = player.check_add_book(&player, inputRank);
        if(bookAdded != 0){
          win = player.game.over(&player);
          if(win == 1) break;
        }
	if(nextCard->rank != inputRank){
          turn = 0;
        }
        else{
         printf("\nPlayer 1 gets another turn");
        }
      }
    } 
  }
    //Player 2's turn
    while((turn == 0) && (win == 0){
      player.display_hand(&player);      //Display player 1's hand
      player.display_book(&comp,1);    //Display player 1's book
      comp.display_book(&comp,2);        //Display player 2's book
      inputRank = player.user_play(&player); //Prompt player 1 to enter a rank
      transferCards = comp.search(&player, inputRank); //Check player 2's hand to see if they have that rank
      if(transferCards == 1){           //If they have the rank transfer the cards
        comp.transfer_cards(&comp, &player, inputRank);
        bookAdded = comp.check_add_book(&comp, inputRank);
        if(bookAdded != 0){
          win = comp.game.over(&comp);
          if(win == 1) break;
	}
	  printf("\nPlayer 2 gets another turn");
        }
        else{                            //If they dont have the card exit the loop and switch to player 2's turn
          printf("Player 1 has no %c's", inputRank);
          card* nextCard = Deck.next_card();  //Draw a card from deck
          printf("\nGo Fish, Player 2 draws %c%c", nextCard->rank, nextCard->suit);
          bookAdded = comp.check_add_book(&player, inputRank);
          if(bookAdded != 0){
            win = comp.game.over(&comp);
            if(win == 1) break;
          }
	  if(nextCard->rank != inputRank){
            turn = 0;
          }
          else{
           printf("\nPlayer 2 gets another turn");
          }
        }
      }
  if(player.game_over(&player) == 1){
    printf("\nPlayer 1 Wins! %d-%d", strlen(player.book), strlen(comp.book));
  }
  else{
    printf("\nPlayer 2 Wins! %d-%d", strlen(comp.book), strlen(player.book));
  }
  printf("\nDo you want to play again?");
  while(playAgain == 0){
    char input = getchar();
    if(input.toLower() == "y"){
      break;
    }
    else if(input == "n"){
      play = 0;
      exit(0);
    }
    else {
      printf("\nError! Please enter Y or N");
    }
  }
//at end output winner and scores(num of books)
//ask if  want to play again, if yes, start loop again, if no, exit
  }
}
