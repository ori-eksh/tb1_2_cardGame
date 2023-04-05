#ifndef CARD_HPP
#define CARD_HPP
#include "iostream"
#include <vector>
#include <random>
namespace ariel
{
    using namespace std;

    enum Rank
    {
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE = 9,
        TEN = 10,
        JACK = 11,
        QUEEN = 12,
        KING = 13,
        ACE = 14,

    };
    enum Suit
    {
        CLUBS = 1,
        DIAMONDS = 2,
        HEARTS = 3,
        SPADES = 4
    };

    class Card
    {
    private:
        Rank rank;
        Suit suit;

    public:
        void printCardD();

        int getRank() { return this->rank; }
        int getSuit() { return this->suit; }

        Card(Rank rank, Suit suit) : rank(rank), suit(suit){};
    };
} // namespace ariel

#endif