# Playing_Card
A simple playing card implementation.

There are 2 classes both in the header file "poker.h".

## Class name: poker_card
 One card with some constructor and the relational operator.
 
### private variable:
```pseudocode!
rank: integer to store the rank of this card.
> 2~10: 2 ~ 10
> 11: Jack
>	12: Queen
> 13: King
> 14: Ace
> 15: Joker

color: character to store the color of this card.
> c: Clubs
> d: Diamonds
> h: Hearts
> s: Spades
```

### public interface:

**Constructor:**

```pseudocode!
poker_card(int rank, char color) ;

// unfinished
poker_card(int rank, string color_string) ;
poker_card(string rank_string, string color_string) ;
poker_card(string input_argument) ;
```

**getRank(), getColor()**
```pseudocode!
getRank(): Return the rank of this card.
getColor(): Return the color of this card.
```

**Relational operator:**

```pseudocode!
A  < B if (A.rank < B.rank) or (A.rank == B.rank and A.color < B.color)

A == B if (A.rank == B.rank) and (A.color == B.color)

The ascending order of color: "Clubs" < "Diamonds" < "Hearts" < "Spades".

Other relational operators defined by the above 2 methods.
```

## Class name: deck
(To be continued.)
