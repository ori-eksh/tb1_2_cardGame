#include "card.hpp"
using namespace ariel;
void Card::printCardD()
{
    switch (this->rank)
    {
    case ACE:
        cout << "Ace";
        break;
    case TWO:
        cout << "Two";
        break;
    case THREE:
        cout << "Three";
        break;
    case FOUR:
        cout << "Four";
        break;
    case FIVE:
        cout << "Five";
        break;
    case SIX:
        cout << "Six";
        break;
    case SEVEN:
        cout << "Seven";
        break;
    case EIGHT:
        cout << "Eight";
        break;
    case NINE:
        cout << "Nine";
        break;
    case TEN:
        cout << "Ten";
        break;
    case JACK:
        cout << "Jack";
        break;
    case QUEEN:
        cout << "Queen";
        break;
    case KING:
        cout << "King";
        break;
    }

    cout << " of ";

    switch (this->suit)
    {
    case CLUBS:
        cout << "Clubs ";
        break;
    case DIAMONDS:
        cout << "Diamonds ";
        break;
    case HEARTS:
        cout << "Hearts ";
        break;
    case SPADES:
        cout << "Spades ";
        break;
    }
}
