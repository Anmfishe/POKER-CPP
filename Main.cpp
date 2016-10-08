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


//Memory leaks



struct Card {
	string suit;
	string face;
	int val;
	bool kept = false;
	Card() {};
	Card(string s, string f, int v) {
		suit = s;
		face = f;
		val = v;
	};
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
void print_options() {
	cout << endl << "OPTIONS:" << endl
		<< "	The letters of the cards you wish to keep (ABCDEF)" << endl
		<< "	DECK - View the cards remaining in the deck" << endl
		<< "	MONEY - View current amount of money" << endl
		<< "	NONE - Discard all your cards" << endl
		<< "	ALL - Keep all cards in your hand" << endl
		<< "	EXIT - Quit out of the game" << endl
		<< "	SWAP - Cheat and swap a card from your hand with a random card from the deck" << endl;
}
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
int random_range(int max) {
	return rand() % max;
}
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
void print_hand(LinkedList<Card> &hand, bool first) {
	
	cout << endl << "Your hand:" << endl;
	for (char i = 'A'; i < 'F'; i++) {
		Card c = hand.find_at_index(i - 65);
		cout << i << ": " << c.face << " of " << c.suit;
		if (c.kept && !first) cout << " (kept)";
		cout << endl;
	}
}
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
bool check_flush(const LinkedList<Card> &hand)
{
	Card c = hand.find_at_index(0);
	string target_suit = c.suit;
	for (int i = 1; i < 4; i++) {
		c = hand.find_at_index(i);
		if (c.suit != target_suit) return false;
	}
	return true;
}
bool check_straight(const LinkedList<Card> &hand)
{
	Card c = hand.find_at_index(0);
	int target_val = c.val + 1;
	for (int i = 1; i < 4; i++) {
		c = hand.find_at_index(i);
		if (c.val != target_val) return false;
		target_val++;
	}
	return true;
}
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
bool evaluate_input(string input, LinkedList<Card> &hand, LinkedList<Card> &deck) {
	if (input.length() > 5) return false;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] < 'A' || input[i] > 'E') {
			return false;
		}
	}
	string holder;
	for (int i = 0; i < input.length(); i++) {
		if (holder.find(input[i]) != string::npos) {
			return false;
		}
		holder.push_back(input[i]);
	}
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
	
	for (int i = 4; i >= 0; i--) 
	{
		if (holder2.length() > 0 && i + 65 == (holder2.back())) {
			holder2.pop_back();
		}
		else {
			hand.find_and_delete_at_index(i);
		}
	}
	
	fill_hand(hand, deck);
	return true;
}
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
	return 0;
}
int main() {
	{
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
	_CrtDumpMemoryLeaks();
	return 0;
}