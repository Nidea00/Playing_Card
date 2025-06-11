#pragma once
#include<string>
#include<stdexcept>

#include<random>
#include<deque>
#include<algorithm>


#define DEFINE_ALL_REL_OPS(type)                                        \
    bool operator!=(const type& rhs) const { return !(*this ==   rhs); }\
    bool operator<=(const type& rhs) const { return !(*this  >   rhs); }\
    bool operator> (const type& rhs) const { return    rhs   < *this ; }\
    bool operator>=(const type& rhs) const { return !(*this  <   rhs); }


static void toLowerCase(std::string& s) ;

static const char invalid_poker_card_message[] = "Arguments of the card is invalid." ;

static const char valid_colors[] = {'c', 'd', 'h', 's'} ;

class poker_card{
private:
	int rank ;
	/*
	2~10: '2'~'10'
	11: Jack
	12: Queen
	13: King
	14: Ace
	15: Joker
	
	1 : Also represent Ace,
	0 : represent Blank
	*/
	char color ;
	/*
	'c': Club
	'd': Diamond
	'h': Heart
	's': Spade
	' ': Joker or Blank
	*/
	void checkValid() ;
	// Throw invalid_argument if Input of the poker card is invalid
	
public:
	poker_card(const int, const char) ;
	poker_card(const int, const std::string) ;
	poker_card(const std::string, const std::string) ;
	poker_card(const std::string) ;
	
	int getRank() const;
	char getColor() const;
	bool operator==(const poker_card&) const ;
	bool operator< (const poker_card&) const ;
	DEFINE_ALL_REL_OPS(poker_card)
};

class deck{
private:
	std::deque<poker_card> container ;
public:
	deck(){}
	deck(const poker_card*, const int) ; // Construct deck with an array of poker_cards.
	deck(const int) ; // Construct n decks of poker_cards.
	deck(const int, const int) ; // Construct n1 decks of poker_cards with n2 jokers.
	//template <typename InputIt> deck(InputIt, InputIt) ;
	
	int length() const; // Return how many poker card in the container.
	bool empty() const; // Return true if the deck is empty, false otherwise.
	
	std::deque<poker_card>::iterator begin() ;
	// Return the iterator pointing to the first element in the private container.
	
	std::deque<poker_card>::iterator end() ;
	// Return the iterator pointing to tge past-the-end element in the private container.
	
	poker_card top() ; // Only return the top card of the deck.
	void pop() ; // Discard the top card of the deck.
	poker_card draw() ; // Take out the top card from the deck and return it.
	
	void push(const poker_card) ; // Insert the card at the end of this deck.
	deck operator+=(deck&) ; // Insert another deck at the end of this deck.
	deck operator+ (deck&) ;
	
	bool operator==(const deck&) const; // Return true if 2 decks have same cards in the same order.
	bool operator< (const deck&) const;
	DEFINE_ALL_REL_OPS(deck)
	
	void sort(); // Sort the deck.
	void shuffle(int); // Using mt19937 method to shuffle the deck with the input seed.
};
