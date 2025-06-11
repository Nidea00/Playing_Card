#include "poker.h"

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

/*
deck::deck(InputIt first, InputIt last){
	for(auto it = first; it!=last; ++it){
		container.push_back(*it) ;
	}
}
*/

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

static void toLowerCase(std::string& s){
	for(char& c: s){
		if('A' <= c && c <= 'Z') c += 32 ;
	}
}
