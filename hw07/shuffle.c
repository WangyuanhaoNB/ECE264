#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void divide(CardDeck orig_deck, CardDeck * upper_deck, CardDeck * lower_deck) 
{
	int l = 0;
	for (int i = 1; i < orig_deck.size; i++)
	{
		l = i - 1;
		upper_deck[l].size = i;
		lower_deck[l].size = orig_deck.size - i;
	for (int n = 0; n < i; n++)
	{
		upper_deck[l].cards[n] = orig_deck.cards[n];
	}
	for (int a = 0; a < (orig_deck.size - i); a++)
	{
		lower_deck[l].cards[a] = orig_deck.cards[a + i];
	}
	}
}
 
void shuff(CardDeck upper_deck, CardDeck lower_deck, CardDeck sd, int upper, int lower)
{
	int uppsize = upper_deck.size;
	int lowsize = lower_deck.size;

	if (upper == uppsize && lowsize == lower)
	{
		print_deck(sd);
		printf("\n");
	}
	else if (uppsize == upper)
	{
		sd.cards[upper + lower] = lower_deck.cards[lower];
		shuff(upper_deck, lower_deck, sd, upper, lower + 1);
	}
	else if (lower == lowsize)
	{
		sd.cards[upper + lower] = upper_deck.cards[upper];
		shuff(upper_deck, lower_deck, sd, upper + 1, lower);
	}
	else
	{
		sd.cards[upper + lower] = upper_deck.cards[upper];
		shuff(upper_deck, lower_deck, sd, upper + 1, lower);

		sd.cards[upper + lower] = lower_deck.cards[lower];
		shuff(upper_deck, lower_deck, sd, upper, lower + 1);
	}
}

void interleave(CardDeck upper_deck, CardDeck lower_deck)
{
	CardDeck sd = 
	{
		.size = (upper_deck.size + lower_deck.size),
		.cards = {0}
	};
	int upper = 0;
	int lower = 0;
	shuff(upper_deck, lower_deck, sd, upper, lower);
}
void shuffle(CardDeck orig_deck) {
	int numpairs = orig_deck.size - 1;

	CardDeck * upper_deck = malloc(sizeof(* upper_deck)* numpairs);
	CardDeck * lower_deck = malloc(sizeof(* lower_deck)* numpairs);

	// allocate memory
	if (upper_deck == NULL || lower_deck == NULL) {
		free(upper_deck);
		free(lower_deck);
	}

	// call divideDeck to fill upper_deck and lower_deck 
	divide(orig_deck, upper_deck, lower_deck);

	while (numpairs > 0) {
		// for each pairs call interleave
		interleave(upper_deck[numpairs - 1], lower_deck[numpairs - 1]);
		numpairs--;
	}
} 
