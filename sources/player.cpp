#include "player.hpp"
#include "card.hpp"
#include "game.hpp"
#include <stdexcept>
#include <string>

Player::Player(string name_p)
{
    this->playername = name_p;
    this->has_played = 0;
    this->cardsTaken = 0;
    this->winCount = 0;
}
Player::Player()
{
    this->playername = "anonymous";
    this->has_played = 0;
    this->cardsTaken = 0;
    this->winCount = 0;
}
int Player::get_hasPlayed()
{
    return has_played;
}

Card Player::getBackCardsToPlay()
{
    return cardsToPlay.back();
}
void Player::popBackcardsToPlay()
{
    cardsToPlay.pop_back();
}
void Player::pushBackcardsToPlay(Card cardToPush)
{
    cardsToPlay.push_back(cardToPush);
}

int Player::stacksize() { return (int)(this->cardsToPlay.size()); }
int Player::cardesTaken() { return this->cardsTaken; }
string Player::getName() { return playername; }
