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
  struct hand* temp;
  user.book[7] = '\0'; 
  computer.book[7] = '\0';

//////////////////////Starts the game/////////////////////////
  while(play==1){                              //start game
    shuffle();                                  //shuffle cards
    deal_player_cards(&user);                //deal cards
    deal_player_cards(&computer);

///////////////////////Loops Through Players////////////////////////////////   
    while(win == 0){

/////////////////////Player 1's Turn///////////////////////////////////
      while((turn==1) && (win == 0)){
        display_hand(&user);                          //Display player 1's hand
      
         display_hand(&computer);

        display_book(&user,1);                        //Display player 1's book 
        display_book(&computer,2);                    //Display user 1's book
        inputRank = user_play(&user);                 //Prompt player 1 to enter a rank
	temp = user->card_list;
        transferCards = search(&computer, inputRank); //Check player 2's hand to see if they have that rank
     /////////////If they have the rank transfer the cards///////////////////////////////////  
	if(transferCards == 1){          
          printf("  - Player 2 has");
  	  transfer_cards(&computer, &user, inputRank);
          bookAdded = check_add_book(&user, inputRank);
          if(bookAdded != 0){
	    print_book_match(bookAdded,temp,1);
            win = game_over(&user);
            if(win == 1) break;
	  }
	  printf("\n  - Player 1 gets another turn");
        }
     ////////////Go Fish/////////////////////////////////////////////////////////////
        else{                          
          printf("  - Player 2 has no %c's", inputRank);
          struct card* nextCard = next_card();  //Draw a card from deck
          add_card(&user, nextCard);
          printf("\n  - Go Fish, Player 1 draws %c%c", nextCard->rank, nextCard->suit);
          bookAdded = check_add_book(&user, inputRank);
          if(bookAdded != 0){
            print_book_match(bookAdded, &temp,1);
            win = game_over(&user);
            if(win == 1) break;
          }
 	  if(nextCard->rank != inputRank){
            printf("\n  - Player 2's turn");
            turn = 0;
          }
          else{
            printf("\n  - Player 1 gets another turn");
          }
        }
      } 

////////////////////Player 2's turn/////////////////////////////////////////////
        while((turn == 0) && (win == 0)){
        display_hand(&user);                               //Display player 1's hand
        display_hand(&computer);
        display_book(&computer,1);                         //Display user 1's book
        display_book(&computer,2);                         //Display user 2's book
        inputRank =  computer_play(&computer);             //Prompt player 1 to enter a rank
	temp = computer->card_list;
        transferCards = search(&user, inputRank);          //Check player 2's hand to see if they have that rank
    ///////////////////////If they have the card - transfer cards//////////////
        if(transferCards == 1){                       
          printf("\n  - Player 1 has");
	  transfer_cards(&user, &computer, inputRank);
          bookAdded = check_add_book(&computer, inputRank);
          if(bookAdded != 0){
	    print_book_match(bookAdded,&temp, 2);
            win = game_over(&computer);
            if(win == 1) break;
 	  }  
	    printf("\nPlayer 2 gets another turn");
        }
    /////////////////////Go Fish//////////////////////////////////////////////
        else{                            //If they dont have the card exit the loop and switch to user 2's turn
          printf("\n  - Player 1 has no %c's", inputRank);
          struct card* nextCard = next_card();  //Draw a card from deck
          add_card(&computer, nextCard);
          printf("\n  - Go Fish, Player 2 draws a card");
          bookAdded = check_add_book(&computer, inputRank);
          if(bookAdded != 0){
	    print_book_match(bookAdded,&temp,2);
            win = game_over(&computer);
            if(win == 1) break;
          }
	  if(nextCard->rank != inputRank){
            printf("\n  - Player 1's turn");
	    turn = 1; 
          }
          else{
           printf("\nPlayer 2 gets another turn");
          }
        }
      }
    }


////////////////////////End of Game!/////////////////////////////////////////////
    if(game_over(&user) == 1){
      printf("\nPlayer 1 Wins! %d-%d", strlen(user.book), strlen(computer.book));
    }
    else if(game_over(&computer) == 1){
      printf("\nPlayer 2 Wins! %d-%d", strlen(computer.book), strlen(user.book));
    }
    else{printf("\nERROR! - No one won!");}
    printf("\nDo you want to play again?");

/////////////////////Play Again///////////////////////////////////////////////

    char input;
    while(playAgain == 0){
      scanf(" %c", &input);
      if(tolower(input) == 'y'){
        reset_player(&user);
	reset_player(&computer);
        break;
      }
      else if(tolower(input) == 'n'){
        play = 0;
        exit(0);
      }
      else {
        printf("\nError! Please enter Y or N");
      }
    }
  }//at end output winner and scores(num of books)
}//ask if  want to play again, if yes, start loop again, if no, exit
 

