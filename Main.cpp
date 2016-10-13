#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif


#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;
//Lets make a card
struct Card {
	string suit;
	string face;
	//We use a val vaiable to evaluate the card, not the face
	//This helps with looking at straights and pairs
	int val;
	bool kept = false;
	Card() {};
	Card(string s, string f, int v) {
		suit = s;
		face = f;
		val = v;
	};
	//We have to write operators for card since my linked list is templated
	bool operator==(const Card &other) {
		if (this->suit == other.suit && this->face == other.face && this->val == other.val) {
			return true;
		}
		else return false;
	};
	friend ostream& operator<<(ostream& os, const Card& card) {
		return os
			<< card.face << " of "
			<< card.suit << " ";
	};
};
//Now the player which just has money and another linked list called hand
struct Player {
	LinkedList<Card> hand;
	int money = 10;
	void print_money() {
		cout << endl << "Your money: $" << money << endl;
	};
	void clear_hand() {
		hand.clear();
	};
	~Player() {
		hand.clear();
	};
};
//These are all the options I currently have for the player
void print_options() {
	cout << endl << "OPTIONS:" << endl
		<< "	The letters of the cards you wish to keep (ABCDEF)" << endl
		<< "	DECK - View the cards remaining in the deck" << endl
		<< "	MONEY - View current amount of money" << endl
		<< "	NONE - Discard all your cards" << endl
		<< "	ALL - Keep all cards in your hand" << endl
		<< "	EXIT - Quit out of the game" << endl
		<< "	SWAP - Cheat and swap a card from your hand with a card from the deck" << endl;
}
//We will use rand to pull random cards from the deck
int random_range(int max) {
	return rand() % max;
}
//The next couple of functions are all of our print statements
void print_decksize(const LinkedList<Card> &deck) {
	cout << endl << "Cards left in deck: " << deck.getSize() << endl;
}
void print_deck(const LinkedList<Card> &deck) {
	for (int i = 0; i < deck.getSize(); i++) {
		Card c = deck.find_at_index(i);
		if (i % 5 == 0) cout << endl;
		if(i != deck.getSize()-1) cout << c.face << " of " << c.suit << ", ";
		else cout << c.face << " of " << c.suit;
	}
}
void print_ante_message() {
	cout << endl << "1 dollar paid to play" << endl;
}
//We sort the hand by finding the smallest val in the linked list then pushing that card onto a card array and deleting from the hand
//We then refill the hand by reconstructing it, pushing back the smallest values first
//THIS FUNCTION ASSUMES THE HAND IS FULL AT 5
void sort_hand(LinkedList<Card> &hand) {
	Card temp_hand[5];
	for (int j = 0; j < 5; j++) {
		int least_index;
		int least_val = 15;
		for (int i = 0; i < hand.getSize(); i++) {
			Card c = hand.find_at_index(i);
			if (c.val < least_val) {
				least_index = i;
				least_val = c.val;
			}
		}
		temp_hand[j] = hand.find_at_index(least_index);
		hand.find_and_delete_at_index(least_index);
	}
	for (int i = 0; i < 5; i++) {
		hand.push_back(temp_hand[i]);
	}
}
//If we are ever getting random cards from the deck and we run out, this is how we refill it
//Maybe there is a better way to do this but creating the array wasn't too bad with copy/paste
void fill_deck(LinkedList<Card> &deck) {
	Card cards[52] = {
		{"Hearts", "Two", 2}, { "Hearts", "Three", 3 }, { "Hearts", "Four", 4 }, { "Hearts", "Five", 5 }, { "Hearts", "Six", 6 }, { "Hearts", "Seven", 7 }, { "Hearts", "Eight", 8 }, { "Hearts", "Nine", 9 }, { "Hearts", "Ten", 10}, { "Hearts" , "Jack", 11}, { "Hearts" , "Queen", 12}, { "Hearts", "King", 13 }, { "Hearts", "Ace", 14 },
		{ "Clubs", "Two", 2 },{ "Clubs", "Three", 3 },{ "Clubs", "Four", 4 },{ "Clubs", "Five", 5 },{ "Clubs", "Six", 6 },{ "Clubs", "Seven", 7 },{ "Clubs", "Eight", 8 },{ "Clubs", "Nine", 9 },{ "Clubs", "Ten", 10 },{ "Clubs" , "Jack", 11 },{ "Clubs" , "Queen", 12 },{ "Clubs", "King", 13 },{ "Clubs", "Ace", 14 },
		{ "Spades", "Two", 2 },{ "Spades", "Three", 3 },{ "Spades", "Four", 4 },{ "Spades", "Five", 5 },{ "Spades", "Six", 6 },{ "Spades", "Seven", 7 },{ "Spades", "Eight", 8 },{ "Spades", "Nine", 9 },{ "Spades", "Ten", 10 },{ "Spades" , "Jack", 11 },{ "Spades" , "Queen", 12 },{ "Spades", "King", 13 },{ "Spades", "Ace", 14 },
		{ "Diamonds", "Two", 2 },{ "Diamonds", "Three", 3 },{ "Diamonds", "Four", 4 },{ "Diamonds", "Five", 5 },{ "Diamonds", "Six", 6 },{ "Diamonds", "Seven", 7 },{ "Diamonds", "Eight", 8 },{ "Diamonds", "Nine", 9 },{ "Diamonds", "Ten", 10 },{ "Diamonds" , "Jack", 11 },{ "Diamonds" , "Queen", 12 },{ "Diamonds", "King", 13 },{ "Diamonds", "Ace", 14 },
	};
	for (int i = 0; i < 52; ++i) {
		deck.push_back(cards[i]);
	}

}
//To get a random card from the deck, we find a random number between 0 and the size of the deck, then remove that card from the deck and put it into the hand
//But if the deck size was 0, we have to refill it then remove any cards in the player's hand from it
void get_random_card(LinkedList<Card> &hand, LinkedList<Card> &deck) {
	if (deck.getSize() == 0) {
		fill_deck(deck);
		for (int i = 0; i < hand.getSize(); i++) {
			deck.find_and_delete(hand.find_at_index(i));
		}
	}
	int index = random_range(deck.getSize());
	Card c = deck.find_at_index(index);
	hand.push_back(c);
	deck.find_and_delete(c);
}
//We do a basic fill the hand until the hand is 5
//The extra code is to set the card variable kept to true. We do this for the  print hand function. This used to not be a problem because
//you could extrapolate from the amount of cards swapped which ones stayed, and they would be at the front.
//This broke when we started sorting the hand which made it so not only the front cards were kept, they could be at any index
//so we wrote this extra code
void fill_hand(LinkedList<Card> &hand, LinkedList<Card> &deck) {
	for (int i = 0; i < hand.getSize(); i++) {
		Card c = hand.find_at_index(i);
		c.kept = true;
		hand.set_at_index(i, c);
	}
	for (int i = hand.getSize(); i < 5; i++) {
		get_random_card(hand, deck);
	}
}
//A simple way to print the hand using a char in our for loop
//If the card was kept then print kept next to it, but not if this is the 'first' time the player is seeing this hand.
//If it is, that means this is a new hand for the player and we wouldnt want to print kept next to 5 new cards
void print_hand(LinkedList<Card> &hand, bool first) {
	
	cout << endl << "Your hand:" << endl;
	for (char i = 'A'; i < 'F'; i++) {
		Card c = hand.find_at_index(i - 65);
		cout << i << ": " << c.face << " of " << c.suit;
		if (c.kept && !first) cout << " (kept)";
		cout << endl;
	}
}
//First we get the letter of the card they are swapping, then the suit and face of the desired card. If it's in the deck, 
//pull the card from the deck and put it in player's hand
//Note we dont actually delete the card from the hand until we can see that the requested card is in the deck.
//If it isn't, dont delete that card and just return false.
bool swap_cards(LinkedList<Card> &hand, LinkedList<Card> &deck) {
	cout << endl << "Please enter letter of the card you want to get rid of:";
	string input;
	cin >> input;
	while (!(input.length() == 1 && input[0] >= 'A' && input[0] <= 'E')) {
		cout << endl << "Try again. Please enter letter of the card you want to get rid of:";
		input.clear();
		cin >> input;
	}
	int index_to_delete = input[0] - 65;
	input.clear();
	cout << endl << "Now enter the face of the card you want (Two, Jack, ect):";
	cin >> input;
	while (input != "Two" && input != "Three" && input != "Four" && input != "Five" && input != "Six" && input != "Seven" && input != "Eight"
		&& input != "Nine" && input != "Ten" && input != "Jack" && input != "Queen" && input != "King" && input != "Ace") {
		cout << endl << "Try again. Enter the face of the card you want (Two, Jack, ect):";
		input.clear();
		cin >> input;
	}
	string desired_face = input;
	input.clear();
	cout << endl << "Now enter the suit of the card you want (Hearts, Diamonds ect):";
	cin >> input;
	while (input != "Hearts" && input != "Clubs" && input != "Diamonds" && input != "Spades") {
		cout << endl << "Try again. Enter the suit of the card you want (Hearts, Diamonds ect):";
		input.clear();
		cin >> input;
	}
	string desired_suit = input;
	for (int i = 0; i < deck.getSize(); i++) {
		Card c = deck.find_at_index(i);
		if (c.face == desired_face && c.suit == desired_suit) {
			hand.set_at_index(index_to_delete, c);
			deck.find_and_delete_at_index(i);
			cout << endl << "Card swapped!" << endl;
			return true;
		}
	}
	cout << endl << "Sorry, that card isn't in the deck" << endl;
	return false;
}
//The next block of functions is evaluating the poker hands
//First is flush which get the suit of the first card, then checks the rest. If a non target suit is found, return false
//If we made it through the for loop, that means we never returned false and we can return true;
bool check_flush(const LinkedList<Card> &hand)
{
	Card c = hand.find_at_index(0);
	string target_suit = c.suit;
	for (int i = 1; i < 5; i++) {
		c = hand.find_at_index(i);
		if (c.suit != target_suit) return false;
	}
	return true;
}
//Sort of like flush, we get the first value in the hand then see if the next one is 1 + the last value
//If it isnt, return false, if we make it through the loop, return true
//Note that because we chose the sort hand optional objective, this function is MUCH easier
bool check_straight(const LinkedList<Card> &hand)
{
	Card c = hand.find_at_index(0);
	int target_val = c.val + 1;
	for (int i = 1; i < 5; i++) {
		c = hand.find_at_index(i);
		if (c.val != target_val) return false;
		target_val++;
	}
	return true;
}
//How we check pairs and three of a kinds is we make an array of ints that goes to 0-14
//Initialize them all at 0
//As we go through the hand, at the card's value in the int array increment that spot by 1
//If any one spot got incremented 3 times, we have three of a kind and we return true
//If we make it out of the for loop without returning true, we didn't find three of a kind and we can return false
bool check_toak(const LinkedList<Card> &hand)
{
	int int_arr[15] = {};
	for (int i = 0; i < 5; i++) {
		Card c = hand.find_at_index(i);
		int_arr[c.val]++;
	}
	for (int i = 0; i < 15; i++) {
		if (int_arr[i] >= 3) {
			return true;
		}
	}
	return false;
}
//Here we do something similar to the three of a kind function, but now we are counting each time a slot has two or more
//If we had two at two different indexes, that means we have two pair
//Note that if a player has a full house they will win with three pair not two pair just because of the order the functions are called
bool check_two_pair(const LinkedList<Card> &hand)
{
	int int_arr[15] = {};
	int counter = 0;
	for (int i = 0; i < 5; i++) {
		Card c = hand.find_at_index(i);
		int_arr[c.val]++;
	}
	for (int i = 0; i < 15; i++) {
		if (int_arr[i] >= 2) {
			counter++;
		}
	}
	if (counter >= 2) return true;
	return false;
}
//Check for pair is similar to pair except without the counter
//Also we start checking the int array at 11 as that is Jacks or higher
bool check_pair(const LinkedList<Card> &hand)
{
	int int_arr[15] = {};
	for (int i = 0; i < 5; i++) {
		Card c = hand.find_at_index(i);
		int_arr[c.val]++;
	}
	for (int i = 11; i < 15; i++) {
		if (int_arr[i] >= 2) {
			return true;
		}
	}
	return false;
}
//After the input from the user is good and we refresh the cards in the user's hand, we can evaluate it
//Note that we check for the highest priority hands first 
//This is so we return first as it doesnt matter if we have a lower hand than the won that returned
//This function also handles the win/loss statements before returning
int evaluate_hand(const LinkedList<Card> &hand) {
	if (check_flush(hand)) {
		cout << endl << "You have a flush! You earned 6 dollars!" << endl;
		return 6;
	}
	else if (check_straight(hand)) {
		cout << endl << "You have a straight! You earned 4 dollars!" << endl;
		return 4;
	}
	else if (check_toak(hand)) {
		cout << endl << "You have three of a kind! You earned 3 dollars!" << endl;
		return 3;
	}
	else if (check_two_pair(hand)) {
		cout << endl << "You have two pairs! You earned 2 dollars!" << endl;
		return 2;
	}
	else if (check_pair(hand)) {
		cout << endl << "You have a pair of Jacks or higher! You earned 1 dollar!" << endl;
		return 1;
	}
	else {
		cout << endl << "Not a winner, sorry!" << endl;
		return 0;
	}
}
//We call this if the input was letter input and not one of the other options
//We have to see if that input was acceptible. Let's step into this one
bool evaluate_input(string input, LinkedList<Card> &hand, LinkedList<Card> &deck) {
	//First, if the string is over five, just return. The biggest input is ABCDE which is 5 long
	if (input.length() > 5) return false;
	//Then make sure each char in the input is between A and E, out acceptible letters
	//If any aren't, return false
	for (int i = 0; i < input.length(); i++) {
		if (input[i] < 'A' || input[i] > 'E') {
			return false;
		}
	}
	//Now we check for duplicates like AA, BB or DCED
	//Make a holder string and start pushing chars into it from input
	//If the holder already has that char in their string, return false
	string holder;
	for (int i = 0; i < input.length(); i++) {
		if (holder.find(input[i]) != string::npos) {
			return false;
		}
		holder.push_back(input[i]);
	}
	//If we got to this point it means the input was good
	//Make holder 2 which is going to be a sorted version of input
	//We do this because we can't delete A before E, the hand doesn't go to E after deleting A. It would be an out of bounds error for my linked list
	//So we sort it then remove from the back
	//We do this by finding the smallest char from input that's not already in holder 2 and pushing it in
	string holder2;
	while (holder2.length() < input.length()) {
		char least = 100;
		for (int i = 0; i < input.length(); i++) {
			if (least > input[i] && holder2.find(input[i]) == string::npos) {
				least = input[i];
			}
		}
		holder2.push_back(least);
	}
	//What we do here is we conver i to a char (sorta) by adding 65
	//If that char is equal to the back of holder, then that means it is one of the cards the player was trying to save
	//Save that card, and remove it from the back holder after we save it
	//If it wasn't one of those cards, remove it from hand
	//Note how we start at 4 and work backwards because we are deleting from the back (in order to not go out of bounds)
	for (int i = 4; i >= 0; i--) 
	{
		if (holder2.length() > 0 && i + 65 == (holder2.back())) {
			holder2.pop_back();
		}
		else {
			hand.find_and_delete_at_index(i);
		}
	}
	//Refill the hand and return true
	
	fill_hand(hand, deck);
	return true;
}
//This is the function that asks for then evaluates input
//Half of these are just informational prints, and they don't return since they don't progress the game
//The game only progresses on ALL, NONE, or good letter input from the player
//Note that only exit return false, the rest either dont return or return true
bool handle_input(Player &player, LinkedList<Card> &deck) {
	string input;
	bool waiting_for_action = true;
	while (waiting_for_action) {
		cin >> input;


		if (input == "EXIT") return false;
		else if (input == "DECK") {
			print_deck(deck);
			print_options();
		}
		else if (input == "MONEY") {
			player.print_money(); 
			print_options();
		}
		else if (input == "SWAP") { 
			swap_cards(player.hand, deck); 
			sort_hand(player.hand); 
			print_decksize(deck);
			print_options();
			print_hand(player.hand, true); 
		}
		else if (input == "NONE") 
		{
			player.clear_hand();
			fill_hand(player.hand, deck);
			sort_hand(player.hand);
			print_hand(player.hand, false);
			player.money += evaluate_hand(player.hand);
			return true;
			
		}
		else if (input == "ALL") 
		{
			fill_hand(player.hand, deck);
			sort_hand(player.hand);
			print_hand(player.hand,  false);
			player.money += evaluate_hand(player.hand);
			return true;
			
		}
		else if (evaluate_input(input, player.hand, deck)) 
		{
			sort_hand(player.hand);
			print_hand(player.hand,  false);
			player.money += evaluate_hand(player.hand);
			return true;
		}
		else
		{
			cout << endl << "I didn't understand that, try again" << endl;
		}
	}
	return true;
}
//Finally, main
//First seed rand
//Make the player, the deck, fill the player's hand, take their money, then print all the options
//If the player typed EXIT, break out of the game
//If the player is out of money after the last round, break out of the game
//Or just hit enter to do it again
//Note that I added brackets to make my linked list variables out of scope before we get to the memory leaks functions
//This way their destructors are called non explicitely so I'm not a bad
int main() {
	{
		srand(time(NULL));
		Player player;
		LinkedList<Card> the_deck;
		fill_deck(the_deck);
		fill_hand(player.hand, the_deck);
		while (true) {
			print_options();
			print_decksize(the_deck);
			print_ante_message();
			player.money--;
			player.print_money();
			sort_hand(player.hand);
			print_hand(player.hand, true);
			if (!handle_input(player, the_deck)) break;
			if (player.money <= 0) { cout << endl << "Out of money. GAME OVER" << endl; system("PAUSE"); break; }
			player.hand.clear();
			fill_hand(player.hand, the_deck);
			cout << endl << "Hit ENTER to continue" << endl;
			cin.ignore(1000, '\n');
			cin.get();
		}
	}
	//I haven't had leaks yet
	//Every push calls a new, every pop calls a delete
	_CrtDumpMemoryLeaks();
	return 0;
}