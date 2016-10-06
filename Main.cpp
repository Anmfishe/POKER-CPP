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
		cout << "Your money: $" << money << endl;
	};
};
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
		for (int i = hand.getSize(); i < 5; i++) {
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
void print_hand(LinkedList<Card> &hand, int cards_kept) {
	for (char i = 'A'; i < 'F'; i++) {
		Card c = hand.find_at_index(i - 65);
		cout << i << ": " << c.face << " of " << c.suit;
		if ((i - 65) < cards_kept) cout << " (kept)";
		cout << endl;
	}
}

int main() {
	Player player;
	LinkedList<Card> Deck;
	fill_deck(Deck);
	fill_hand(player.hand, Deck);
	print_hand(player.hand, 5);
	system("pause");
	return 0;
}