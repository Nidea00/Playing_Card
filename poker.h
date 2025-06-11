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


static void toLowerCase(std::string& s){
	for(char& c: s){
		if('A' <= c && c <= 'Z') c += 32 ;
	}
}
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
	template <typename InputIt> deck(InputIt, InputIt) ;
	
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

void poker_card::checkValid(){
	// Check rank
	if(rank == 1) rank = 14 ; // Replace 1 to Ace.
	else if(rank<0 || rank>15) throw std::invalid_argument(invalid_poker_card_message) ;
	
	// Check color
	if(rank == 0 || rank == 15){
		color = ' ' ;
		return ;
	}
	for(char c: valid_colors){
		if(color == c) return ;
	}
	
	throw std::invalid_argument(invalid_poker_card_message) ;
}

// Constructor of poker_card
poker_card::poker_card(const int rnk, const char c)
:rank(rnk), color(tolower(c)){
	checkValid() ;
}
poker_card::poker_card(const int rnk, const std::string color_str)
:poker_card(rnk, tolower(color_str[0])) {}
// Warning: We only check whether color_str[0] in valid_colors.

// Get the information of the card.
int poker_card::getRank() const{
	return rank ;
}
char poker_card::getColor() const{
	return color ;
}

// Operator overloading
bool poker_card::operator==(const poker_card& rhs) const{
	return color == rhs.color && rank == rhs.rank ;
}
bool poker_card::operator<(const poker_card& rhs) const{
	if(rank < rhs.rank) return true ;
	else if(rank > rhs.rank) return false ;
	
	if(color < rhs.color) return true ;
	return false ;
}

// Constructor of deck
deck::deck(const poker_card* card_arr, const int n){
	for(int offset=0; offset<n; offset++){
		container.push_back(card_arr[offset]) ;
	}
}

deck::deck(const int n_deck){
	for(int rank = 2; rank<=14; rank++){
		for(char color:valid_colors){
			for(int i=0; i<n_deck; i++){
				container.push_back(poker_card(rank, color)) ;
			}
		}
	}
}

deck::deck(const int n_deck, const int n_joker)
:deck(n_deck){
	for(int i=0; i<n_joker; i++){
		container.push_back(poker_card(15, ' ')) ;
	}
}

template <typename InputIt> deck::deck(InputIt first, InputIt last){
	for(auto it = first; it!=last; ++it){
		container.push_back(*it) ;
	}
}

// Information
int deck::length() const{
	return container.size() ;
}

bool deck::empty() const{
	return container.empty() ;
}

// Iterator
std::deque<poker_card>::iterator deck::begin(){
	return container.begin() ;
}

std::deque<poker_card>::iterator deck::end(){
	return container.end() ;
}

// Method about Output
poker_card deck::top(){
	return container.front() ;
}

void deck::pop(){
	container.pop_back() ;
}

poker_card deck::draw(){
	poker_card drawn_card = container.front() ;
	container.pop_back() ;
	return drawn_card ;
}

// Method about Input
void deck::push(const poker_card card){
	container.push_back(card) ;
}

deck deck::operator+=(deck& additive){
	for(poker_card card: additive){
		container.push_back(card) ;
	}
	
	return *this ;
}

deck deck::operator+(deck& additive){
	deck merged = *this ;
	
	for(poker_card card: additive){
		merged.push(card) ;
	}
	
	return merged ;
}

// Relational Operator
bool deck::operator==(const deck& rhs) const{
	return container == rhs.container ;
}
bool deck::operator< (const deck& rhs) const{
	return container < rhs.container ;
}

// Other method
void deck::sort(){
	std::sort(container.begin(), container.end()) ;
}

void deck::shuffle(int seed){
	std::shuffle(container.begin(), container.end(), std::mt19937(seed)) ;
}