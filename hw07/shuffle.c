#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// You may add more functions in this file.
void deck_recursion(char* ,char* ,char* ,int ,int ,int ,int );

void divide(CardDeck orig_deck, CardDeck * upper_deck, CardDeck * lower_deck) {
	int i,j;//index for CardDeck * and upper deck
	int k = 0;//index for lower deck
	for(i = 0;i < orig_deck.size - 1;i++){
		k = 0;
		upper_deck[i].size = i + 1;
		lower_deck[i].size = orig_deck.size - i - 1;
		for(j = 0; j < orig_deck.size; j++){
		  if (j < i + 1){
			upper_deck[i].cards[j] = orig_deck.cards[j];
		  }
		  else{
			lower_deck[i].cards[k] = orig_deck.cards[j];
			k++;
		  }
	    }
	}	
}

void interleave(CardDeck upper_deck, CardDeck lower_deck) {
	int UpperLength = upper_deck.size;
	int LowerLength = lower_deck.size;
	int length = UpperLength + LowerLength;
	char * OutputDeck = malloc(length * sizeof(char));//alloc
	deck_recursion(upper_deck.cards,lower_deck.cards,OutputDeck,UpperLength,LowerLength,0,length);
	free(OutputDeck);//free
}

void deck_recursion(char* upper_deck,char* lower_deck,char* output_deck,int upper_length,int lower_length,int i,int length){
	if (upper_length == 0 && lower_length == 0){
		CardDeck output;
		strncpy(output.cards,output_deck,length);
		output.size = length;
		print_deck(output);
		printf("\n");
	}
	//set the first value of upper or lower deck and call the other ones recursively
	if (upper_length != 0){
		output_deck[i] = upper_deck[0];
		deck_recursion(upper_deck + 1,lower_deck,output_deck,upper_length - 1,lower_length,i + 1,length);
	}
	if (lower_length != 0){
		output_deck[i] = lower_deck[0];
		deck_recursion(upper_deck,lower_deck + 1,output_deck,upper_length,lower_length - 1,i + 1,length);
	}
}	

void shuffle(CardDeck orig_deck) {
	int numpairs = orig_deck.size - 1;

	// allocate memory
	CardDeck * upper_deck = malloc((orig_deck.size - 1) * sizeof(CardDeck));
	CardDeck * lower_deck = malloc((orig_deck.size - 1) * sizeof(CardDeck));

	divide(orig_deck,upper_deck,lower_deck);
	// call divideDeck to fill upper_deck and lower_deck 
	int i = 0;
	while (numpairs > 0) {
		// for each pairs call interleave
		interleave(upper_deck[i],lower_deck[i]);
		i++;
		numpairs--;
	}
		free(upper_deck);//free
		free(lower_deck);//free
} 
