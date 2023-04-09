#ifndef GAME_HPP
#define GAME_HPP
#include "card.hpp"
#include "player.hpp"
#include <vector>
using namespace ariel;

namespace ariel
{
}

class Game
{
private:
    Player &p1;
    Player &p2;
    vector<Card> cards;
    string winTurn;
    int gameAlive; // 0- game over  1- game alive
    vector<Card> lastMoove1;
    vector<Card> lastMoove2;

    vector<Card> allMooves1;
    vector<Card> allMooves2;
    int tekoTimeCount;
    int teko_time;
    int rounds;

public:
    Game(Player &pp1, Player &pp2);
    Game();

    void Reset_package();
    void Dealing_cards();
    void Card_shuffling();

    void playTurn();
    void printLastTurn();
    void playAll();
    void printWiner();
    void printLog();
    void printStats();
    Player getPlayer1(); //
    Player getPlayer2(); //
    void tekoTimeCountAdd() { tekoTimeCount++; }
    int getTekoTime() const { return tekoTimeCount; } // in all the game
    int geteko_time() const { return teko_time; }     // in this round
    void setteko_time(int num) { this->teko_time = num; }

    int getgameAlive() const { return gameAlive; }
    void setgameAlive(int num) { this->gameAlive = num; }

    void roundsAdd() { rounds++; }
    int getrounds() const { return rounds; }
};

#endif