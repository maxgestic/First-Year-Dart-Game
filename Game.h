//
// Created by Max Ring on 25/03/2020.
//
#include <iostream>
#include "Player.h"

using namespace std;

class Game{

private:
    bool active = false;

    int activePlayer, GameWinner, p1Score, p2Score;



public:
    Game(string, int, string, int);

    Game(string, int, int);

    Game(string, int, string, int, bool);

    int ActiveGame(Player &, Player &);

    int InterActiveGame(Player &, Player &);

    int ActiveGameFlip(Player &, Player &);

    void setActive(bool);

    bool getActive();

    void setAPlayer(int);

    int getAPlayer();

    void setWinner(int);

    int getWinner();

    void p1SetScore(int);

    int p1GetScore();

    void p2SetScore(int);

    int p2GetScore();

    int Turn(Player &, Player &);

    int VerboseTurn(Player &, Player &);

    int InterTurn(Player &, Player &);

    int EndTurnCheckDB(int, Player &, Player &);

    int EndTurnCheckNormal(int, Player &, Player &);

    int EndGame(Player &, Player &);
};