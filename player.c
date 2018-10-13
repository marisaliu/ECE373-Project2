#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "player.h"

////////////////////////////////////////////////////////////////
//////////Adds a new card to the player's hand /////////////////
////////Returns 0 if no error, returns -1 if error//////////////
////////////////////////////////////////////////////////////////
int add_card(struct player* target, struct card* new_card)
{
  struct hand* temp;
  temp = (struct hand*)malloc(sizeof(struct hand));
  if(temp ==NULL){ return -1;}
  temp->top = *new_card;
  temp->next = target->card_list;
  target->card_list = temp;
  return 0; //if no error return non-zero otherwise
}



/////////////////////////////////////////////////////////////////
//////////////////Removes card from the hand/////////////////////
/////////////Returns 0 if no error, returns -1 if error//////////
/////////////////////////////////////////////////////////////////
int remove_card(struct player* target, struct card* old_card)
{
  struct hand* iterator = target->card_list;
  struct hand* previous = NULL;
  if(iterator == NULL){ return -1;} //Error list is empty
  while ((iterator->top.rank != old_card->rank) || (iterator->top.suit != old_card->suit))
  {
    previous = iterator;
    iterator = iterator->next;
    if(iterator == NULL) return -1; //Error not in list
  }
  if(previous != NULL) previous->next = iterator->next;
  else
  {
    target->card_list = iterator->next;
  }
  free(iterator);
  return 0;     //returns 0 because we found and removed the card from the hand
}



/////////////////////////////////////////////////////////////////////////////////////////////////
//Checks if there is a book in the hand. If there is it removes the associated cards from the hand.
/////Returns a char that indicates the book that was added, returns 0 if no book was added///////
///////////////////////////////////////////////////////////////////////////////////////////////////
char check_add_book(struct player* target, char search_rank)
{
  int count = 0;
  struct hand* temp;
  temp = target->card_list;
  while(temp != NULL)
  {
    if(temp->top.rank == search_rank) count++;
    temp = temp->next;
  }
  if(count == 4) //if there is a book it removes the associated cards
  {
    for(count; count > 0; count--)
    {
      struct hand* iterator = target->card_list;
      struct hand* previous = NULL;
      while(iterator->top.rank != search_rank)
      {
	previous = iterator;
	iterator = iterator->next;
      }
      if(previous != NULL) previous->next = iterator->next;
      else{ target->card_list = iterator->next;}
      free(iterator);
    }
    return search_rank;
  }
  return 0; //no book was found 
}


//////////////////////////////////////////////////////////////
///////////Searches a player's hand for a requested rank//////
////////Returns 1 if rank is found, returns 0 if not /////////
//////////////////////////////////////////////////////////////
int search(struct player* target, char rank)
{
  struct hand* temp = target->card_list;
  while(temp != NULL)
  {
    if(temp->top.rank == rank){ return 1;}
    temp = temp->next;
  }
  return 0; //if rank not found
}


/*////////////////////////////////////////////////////////////////////
 * Transfer cards of a given rank from the source player's hand to the 
 * destination player's hand. Remove transferred cards from the source
 * player's hand. Add transferred cards to the destination player's hand
 * Return 0 if no cards found/transferred, -1 if error, or value that 
 * indicates number of cards transferred
 *///////////////////////////////////////////////////////////////////
int transfer_cards(struct player* src, struct player* dest, char rank)
{
  int error;
  struct hand* temp = src->card_list;
  while(temp!=NULL)
  {
    if(temp->top.rank == rank){
      error = remove_card(src, &(temp->top));
      if(error == -1) return -1;
      error = add_card(dest, &(temp->top));
      if(error == -1) return -1;
      temp = src->card_list;
    }
    else{ temp = temp->next;}
  }
  return 0;
}



/////////////////////////////////////////////////////////////////////////////////
/////Boolean function to check if a player has 7 books yet and the game is over//
///////////////Returns 1 if game is over, 0 if game is not over//////////////////
/////////////////////////////////////////////////////////////////////////////////
int game_over(struct player* target)
{
  if(strlen(target->book)==7){ return 1;}
  return 0;
}


/////////////////////////////////////////////////////////////////////////////
/////Reset player by free'ing any memory and reinitializes the book./////////
//////////////////Returns 0 if no error, and -1 on error/////////////////////
/////////////////////////////////////////////////////////////////////////////
int reset_player(struct player* target)
{
  target->book[7] = '\0';
  struct hand* temp = NULL;
  while(target->card_list != NULL)
  {
    temp = target->card_list;
    target->card_list = temp->next;
    free(temp);
  }
  return 0;
}


////////////////////////////////////////////////////////////////////////////
///Selects a rank randomly from the computer hands to play//////////////////
//////////Returns a valid selected rank/////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
char computer_play(struct player* target)
{
  char *stringRank = "";
  struct hand* temp = target->card_list;
  int count = 0;
  srand(time(0));
  while(temp != NULL)       //Loops through the linked list and adds the rank to a char array
  {
    stringRank[count] = temp->top.rank;
    temp = temp->next;
  }
  //Picks a random index to access in the char array and returns that char
  int max = strlen(stringRank);
  int index = rand() % max;
  return stringRank[index];
}




///////////////////////////////////////////////////////////////////////////
/////Reads standard input to get rank that user wishes to play////////////
/////////Returns a valid selected rank////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
char user_play(struct player* target)
{
 ;  
char input;
  int boolInHand = 0;
  while(boolInHand == 0)
  {
    printf("\nPlayer 1's turn, enter a Rank: ");
    scanf(" %c",&input);   
    struct hand* temp = target->card_list;
    while(temp != NULL)
    {
      if(temp->top.rank== toupper(input))
      { 
        boolInHand = 1;
        return input;
      }
      temp = temp->next;
    }
    printf("\nError = must have at least one card from rank to play");
  }
}

/////////////////////////////////////////
void display_hand(struct player* target){
  printf("\nPlayer 1's Hand -");
  struct hand* temp = target->card_list;
  while(temp != NULL){
    printf(" %c%c", temp->top.rank, temp->top.suit);
    temp = temp->next; 
 }
}

void display_book(struct player* target, int id){
  printf("\nPlayer %d's Book - ", id);
  printf("%s", target->book);
}
