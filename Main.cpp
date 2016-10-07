#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;


struct Card {
	string suit;
	string face;
	int val;
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
void print_decksize(LinkedList<Card> deck) {
	cout << endl << "Cards left in deck: " << deck.getSize() << endl;
}
void print_ante_message() {
	cout << endl << "1 dollar paid to play" << endl;
}
int random_range(int max) {
	return rand() % max;
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
	for (int i = hand.getSize(); i < 5; i++) {
		get_random_card(hand, deck);
	}
}
void print_hand(LinkedList<Card> &hand, int num_cards_swapped, bool first) {
	int cards_kept = 5 - num_cards_swapped;
	cout << endl << "Your hand:" << endl;
	for (char i = 'A'; i < 'F'; i++) {
		Card c = hand.find_at_index(i - 65);
		cout << i << ": " << c.face << " of " << c.suit;
		if ((i - 65) < cards_kept && !first) cout << " (kept)";
		cout << endl;
	}
}
void swap_cards(LinkedList<Card> &hand, LinkedList<Card> &deck) {

}
int evaluate_hand(const LinkedList<Card> &hand) {
	return 0;
}
bool evaluate_input(string input, LinkedList<Card> &hand, LinkedList<Card> &deck, int &num_cards_swapped) {
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
	num_cards_swapped = 5 - holder2.length();
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
bool handle_input(Player &player, LinkedList<Card> &deck, int &num_cards_swapped) {
	string input;
	bool waiting_for_action = true;
	while (waiting_for_action) {
		cin >> input;


		if (input == "EXIT") return false;
		else if (input == "DECK") {
			deck.print(); 
			print_options();
		}
		else if (input == "MONEY") {
			player.print_money(); 
			print_options();
		}
		else if (input == "SWAP") swap_cards(player.hand, deck);
		else if (input == "NONE") 
		{
			player.clear_hand();
			num_cards_swapped = 5;
			fill_hand(player.hand, deck);
			print_hand(player.hand, num_cards_swapped, false);
			player.money += evaluate_hand(player.hand);
			return true;
			
		}
		else if (input == "ALL") 
		{
			num_cards_swapped = 0;
			print_hand(player.hand, num_cards_swapped, false);
			player.money += evaluate_hand(player.hand);
			return true;
			
		}
		else if (evaluate_input(input, player.hand, deck, num_cards_swapped)) 
		{
			print_hand(player.hand, num_cards_swapped, false);
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
	Player player;
	LinkedList<Card> the_deck;
	fill_deck(the_deck);
	fill_hand(player.hand, the_deck);
	while (true) {
		int num_cards_swapped = 0;
		print_options();
		print_decksize(the_deck);
		print_ante_message();
		player.money--;
		player.print_money();
		print_hand(player.hand, num_cards_swapped, true);
		if(!handle_input(player, the_deck, num_cards_swapped)) break;
		if (player.money <= 0) { cout << endl << "Out of money. GAME OVER" << endl; system("PAUSE"); break; }
		player.hand.clear();
		fill_hand(player.hand, the_deck);
		cout << endl << "Hit any button to continue" << endl;
		cin.get();
		system("PAUSE");

	}
	return 0;
}