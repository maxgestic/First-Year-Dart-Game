//
// Created by Max Ring on 25/03/2020.
//
#include <iostream>
#pragma once

using namespace std;

class Player{

private:
    int score, skill, totalThrows;

    string name;

public:
    Player(string, int);
    int getScore();
    void setScore(int);
    int throw_bull();
    int throw_treble(int);
    int throw_double(int);
    int throw_single(int);

};