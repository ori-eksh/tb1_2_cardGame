#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include <vector>
#include "card.hpp"

using namespace ariel;

using namespace std;

class Player
{
private:
    string playername;
    int has_played;
    int cardsTaken;
    vector<Card> cardsToPlay;

public:
    Card getBackCardsToPlay();
    void popBackcardsToPlay();
    void pushBackcardsToPlay(Card cardtopush);
    int cardsToPlaySize() { return (int)cardsToPlay.size(); }
    void zerocardstoplay() { cardsToPlay.clear(); }

    void setcardsTaken(int fix) { this->cardsTaken = fix; }
    int getcardsTaken() const { return this->cardsTaken; }

    Player(string name_p);
    Player();
    int get_hasPlayed();
    void set_hasPlayed()
    {
        this->has_played = 1;
    }
    int stacksize();
    int cardesTaken();
    string getName();
};

#endif