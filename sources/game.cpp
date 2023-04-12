#include "player.hpp"
#include "game.hpp"
#include "card.hpp"
#include <stdexcept>
#include <string>
#include <iostream>
using namespace std;
Player p1_("");
Player p2_("");

Game::Game() : p1(p1_), p2(p2_) {}

Game::Game(Player &p1, Player &p2) : p1(p1), p2(p2)
{
    {
        if ((p1.get_hasPlayed()) == 1 || (p2.get_hasPlayed()) == 1)
        {
            throw string("cant play again");
        }
        else
        {
            this->rounds = 0;
            this->tekoTimeCount = 0;
            this->allMooves1.clear();
            this->allMooves2.clear();

            this->lastMoove1.clear();
            this->lastMoove2.clear();
            this->gameAlive = 1;
            this->teko_time = 0;
            vector<Card> cards;
            this->cards = cards;
            this->p1 = p1;
            this->p2 = p2;
            p1.set_hasPlayed();
            p2.set_hasPlayed();
            Reset_package();  // now we have the cards
            Card_shuffling(); // now the cards is shuffling
            Dealing_cards();  // Now each player has 26 cards
        }
    }
}

/********************************************************************************************************************************/
Player Game::getPlayer1()
{
    return p1;
}
Player Game::getPlayer2()
{
    return p2;
}
/********************************************************************************************************************************/
void Game::Reset_package() // Initializing a deck of cards
{
    cards.clear(); // clear the current deck of cards

    // add all 52 cards to the deck
    for (int i = 2; i <= 14; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            this->cards.push_back(Card(static_cast<Rank>(i), static_cast<Suit>(j)));
        }
    }
}
/********************************************************************************************************************************/
/*shuffling the cards*/
void Game::Card_shuffling() // I consulted with Alon mwshulam
{
    /*choos random num*/

    random_device rd;
    mt19937 gen(rd());

    /*shuffling the cards*/

    vector<Card> help_pack1;
    vector<Card> help_pack2;

    for (int i = 0; i < 150; i++)
    {
        uniform_int_distribution<> dist(1, 5);
        int rand_num = dist(gen);

        while ((this->cards.empty() != 1) && (this->cards.size() >= (rand_num * 2)))
        {
            for (int i = 0; i < rand_num; i++)
            {
                help_pack1.push_back((this->cards).back());
                this->cards.pop_back();
            }

            for (int i = 0; i < rand_num; i++)
            {
                help_pack2.push_back((this->cards).back());
                this->cards.pop_back();
            }
        }

        while (help_pack1.empty() != 1)
        {
            this->cards.push_back(help_pack1.back());
            help_pack1.pop_back();
        }

        while (help_pack2.empty() != 1)
        {
            this->cards.push_back(help_pack2.back());
            help_pack2.pop_back();
        }
    }
}
/********************************************************************************************************************************/
void Game::Dealing_cards() // Dealing the cards to the players
{

    for (int i = 0; i < 26; i++)
    {
        this->p1.pushBackcardsToPlay(this->cards.back());
        this->cards.pop_back();
        this->p2.pushBackcardsToPlay(this->cards.back());
        this->cards.pop_back();
    }
}
/*******************************************************************************************************************************/
void Game::playTurn()
{
    if (this->getgameAlive() == 0 || (this->p1.getName() == this->p2.getName())) // game over
    {
        throw string("cant play again\n");
    }
    if (this->p1.cardsToPlaySize() == 0) // game over but we came from teko
    {
        this->p1.setcardsTaken(this->p1.getcardsTaken() + (this->geteko_time() * 4));
        this->p2.setcardsTaken(this->p2.getcardsTaken() + (this->geteko_time() * 4));
        this->setteko_time(0);
        this->setgameAlive(0);

        return;
    }
    /* if we start new turn we need to delete the last moove*/
    if (this->geteko_time() == 0)
    {
        this->lastMoove1.clear();
        this->lastMoove2.clear();
    }
    if (this->geteko_time() == 0)
    {
        roundsAdd();
    }

    this->allMooves1.push_back(p1.getBackCardsToPlay());
    this->allMooves2.push_back(p2.getBackCardsToPlay());

    Card card1 = this->p1.getBackCardsToPlay();
    Card card2 = this->p2.getBackCardsToPlay();
    this->p1.popBackcardsToPlay();
    this->p2.popBackcardsToPlay();
    this->lastMoove1.push_back(card1);
    this->lastMoove2.push_back(card2);

    // this->allMooves1.push_back(card1);
    // this->allMooves2.push_back(card2);

    if ((card1.getRank() == 2 && card2.getRank() == 14) || (card1.getRank() > card2.getRank())) // p1 win
    {
        this->p1.winCountAdd(); // winning times in the game
        this->winTurn = this->p1.getName();
        this->p1.setcardsTaken(this->p1.getcardsTaken() + 2);
        this->p1.setcardsTaken(this->p1.getcardsTaken() + (this->geteko_time() * 4));
        this->setteko_time(0);

        if (this->p1.cardsToPlaySize() == 0) // this is the last card
        {
            this->setgameAlive(0);
            this->setteko_time(0);
            this->p1.zerocardstoplay();
            this->p2.zerocardstoplay();
            return;
        }
    }

    else if ((card1.getRank() == 14 && card2.getRank() == 2) || (card1.getRank() < card2.getRank())) // p2 win
    {
        this->p2.winCountAdd(); // winning times in the game
        this->winTurn = this->p2.getName();
        this->p2.setcardsTaken(this->p2.getcardsTaken() + 2);
        this->p2.setcardsTaken(this->p2.getcardsTaken() + (this->geteko_time() * 4));
        this->setteko_time(0);

        if (this->p1.cardsToPlaySize() == 0) // this is the last card
        {
            this->setgameAlive(0);
            this->setteko_time(0);
            this->p1.zerocardstoplay();
            this->p2.zerocardstoplay();

            return;
        }
    }

    else if (card1.getRank() == card2.getRank()) // teko
    {
        tekoTimeCountAdd();
        if (this->p1.cardsToPlaySize() == 0) // this is the last card
        {
            int teplus = this->geteko_time();
            this->setteko_time(teplus + 1);
            this->winTurn = "teko";

            this->p1.setcardsTaken(this->p1.getcardsTaken() + 1);
            this->p1.setcardsTaken(this->p1.getcardsTaken() + (this->geteko_time() * 2));
            // Each player takes his stack

            this->p2.setcardsTaken(this->p2.getcardsTaken() + 1);
            this->p2.setcardsTaken(this->p2.getcardsTaken() + (this->geteko_time() * 2));
            // Each player takes his stack
            this->setgameAlive(0);
            this->p1.zerocardstoplay();
            this->p2.zerocardstoplay();

            return;
        }

        else
        {
            int teplus = this->geteko_time();
            this->setteko_time(teplus + 1);
            this->p1.popBackcardsToPlay();
            this->p2.popBackcardsToPlay();
            this->playTurn();
        }
    }
}
/*******************************************************************************************************************************/
void Game::printLastTurn()
{
    int teko_time_in_this_turn = this->lastMoove1.size() - 1;
    for (int i = 0; i < this->lastMoove1.size(); i++)
    {
        cout << this->p1.getName() << " played ";
        this->lastMoove1.back().printCardD();
        cout << this->p2.getName() << " played ";
        this->lastMoove2.back().printCardD();
        if (teko_time_in_this_turn != 0 && (this->lastMoove1.back().getRank()) == (this->lastMoove2.back().getRank()))
        {
            cout << " Draw ";
        }
        this->lastMoove1.pop_back();
        this->lastMoove2.pop_back();
    }

    if (this->winTurn == " teko ")
    {
        cout << " teko ";
        return;
    }
    cout << this->winTurn;
    cout << " win\n";
}
/*******************************************************************************************************************************/
void Game::playAll()
{
    if (this->getgameAlive() != 0)
    {

        int max_turns = 26;
        while (max_turns != 0 && this->getgameAlive() != 0)
        {
            playTurn();
            max_turns--;
        }
    }
    else
    {
        throw string("cant play again");
    }
}
/*******************************************************************************************************************************/
void Game::printWiner()
{
    if (this->p1.getcardsTaken() > this->p2.getcardsTaken())
    {
        cout << this->p1.getName();
        cout << " win";
    }

    if (this->p1.getcardsTaken() < this->p2.getcardsTaken())
    {
        cout << this->p2.getName();
        cout << " win";
    }

    if (this->p1.getcardsTaken() == this->p2.getcardsTaken())
    {
        throw string("teko");
    }
    cout << "\n";
}
/*******************************************************************************************************************************/
void Game::printLog()
{
    int teko_time_in_this_turn = this->lastMoove1.size() - 1;
    for (int i = 0; i < this->allMooves1.size(); i++)
    {
        cout << this->p1.getName() << " played ";
        this->allMooves1.back().printCardD();
        cout << this->p2.getName() << " played ";
        this->allMooves2.back().printCardD();
        if (teko_time_in_this_turn != 0 && (this->allMooves1.back().getRank()) == (this->allMooves2.back().getRank()))
        {
            cout << "Draw ";
        }
        else
        {
            cout << "\n";
        }
        this->allMooves1.pop_back();
        this->allMooves2.pop_back();
    }
    cout << "\n";

    if (this->winTurn == "teko")
    {
        cout << "teko ";
        return;
    }
    cout << this->winTurn;
    cout << " win\n";
}
/*******************************************************************************************************************************/
void Game::printStats()
{
    printLog();
    int rounds = 26 - this->geteko_time();
    double sec1 = (p1.getWinsOfRounds() * 100) / this->getrounds();
    double sec2 = (p2.getWinsOfRounds() * 100) / this->getrounds();
    double tekostatic = (this->getTekoTime() * 100) / this->getrounds();

    cout << "player 1 - ";
    cout << this->p1.getName();
    cout << " win ";
    cout << this->p1.getWinsOfRounds() << " times, from " << rounds << " rounds.(without the teko time)\n";
    cout << "winning percentage: " << sec1 << "%\n";

    cout << "player 2 - ";
    cout << this->p2.getName();
    cout << " win ";
    cout << this->p2.getWinsOfRounds() << " times, from " << rounds << " rounds.(without the teko time)\n";
    cout << "winning percentage: " << sec2 << "%\n";
    cout << "teko times: " << this->getTekoTime() << "\n";
    cout << "teko percentage: " << tekostatic << "%\n";
    // ori 213562069
}
