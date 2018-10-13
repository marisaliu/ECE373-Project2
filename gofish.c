#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "deck.h"
#include "player.h"
#include <ctype.h>
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
  user.book[7] = '\0'; 
  computer.book[7] = '\0';
 
  shuffle(); 
  deal_player_cards(&user);
  display_hand(&user);
  deal_player_cards(&computer);
  display_hand(&computer);
  inputRank = user_play(&user);
  transferCards = search(&user, inputRank);
  if(transferCards == 1){
    transfer_cards(&user, &computer, inputRank);
  }
}

//  struct deck Deck;
//  struct user player, computer;
/*  while(play==1){                              //start game
    shuffle();                                  //shuffle cards
    deal_player_cards(&user);                //deal cards
    deal_player_cards(&computer);
    while(win == 0){
      //Player 1 starts
      while((turn==1) && (win == 0)){
        display_hand(&user);       //Display player 1's hand
        display_book(&user,1);     //Display player 1's book 
        display_book(&computer,2);         //Display user 1's book
        inputRank = user_play(&user); //Prompt player 1 to enter a rank
        transferCards = search(&user, inputRank); //Check player 2's hand to see if they have that rank
        if(transferCards == 1){           //If they have the rank transfer the cards
          transfer_cards(&user, &computer, inputRank);
          bookAdded = check_add_book(&user, inputRank);
          if(bookAdded != 0){
            win = game_over(&user);
            if(win == 1) break;
	  }
	  printf("\nPlayer 1 gets another turn");
        }
        else{                            //If they dont have the card exit the loop and switch to user 2's turn
          printf("Player 2 has no %c's", inputRank);
          struct card* nextCard = next_card();  //Draw a card from deck
          printf("\nGo Fish, Player 1 draws %c%c", nextCard->rank, nextCard->suit);
          bookAdded = check_add_book(&user, inputRank);
          if(bookAdded != 0){
            win = game_over(&user);
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
    //Player 2's turn
      while((turn == 0) && (win == 0)){
        display_hand(&user);      //Display player 1's hand
        display_book(&computer,1);    //Display user 1's book
        display_book(&computer,2);        //Display user 2's book
        inputRank = user_play(&user); //Prompt player 1 to enter a rank
        transferCards = search(&user, inputRank); //Check player 2's hand to see if they have that rank
        if(transferCards == 1){           //If they have the rank transfer the cards
          transfer_cards(&computer, &user, inputRank);
          bookAdded = check_add_book(&computer, inputRank);
          if(bookAdded != 0){
            win = game_over(&computer);
            if(win == 1) break;
 	  }  
	    printf("\nPlayer 2 gets another turn");
        }
        else{                            //If they dont have the card exit the loop and switch to user 2's turn
          printf("Player 1 has no %c's", inputRank);
          struct card* nextCard = next_card();  //Draw a card from deck
          printf("\nGo Fish, Player 2 draws %c%c", nextCard->rank, nextCard->suit);
          bookAdded = check_add_book(&user, inputRank);
          if(bookAdded != 0){
            win = game_over(&computer);
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
      if(game_over(&user) == 1){
        printf("\nPlayer 1 Wins! %d-%d", strlen(user.book), strlen(computer.book));
      }
      else{
        printf("\nPlayer 2 Wins! %d-%d", strlen(computer.book), strlen(user.book));
      }
      printf("\nDo you want to play again?");
      while(playAgain == 0){
        char input = getchar();
        if(tolower(input) == 'y'){
          break;
        }
        else if(input == 'n'){
          play = 0;
          exit(0);
        }
        else {
          printf("\nError! Please enter Y or N");
        }
      }
    }
  }//at end output winner and scores(num of books)
}//ask if  want to play again, if yes, start loop again, if no, exit
*/  

