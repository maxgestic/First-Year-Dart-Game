//
// Created by Max Ring on 25/03/2020.
//
#include "Game.h"
#include <iostream>
#include <algorithm>

using namespace std;

//Three overloaded constructors to allow for the different options, single sim, sultiple sim and interactive game

Game::Game(string p1N, int p1S, string p2N, int p2S){

    Player p1(p1N, p1S);

    Player p2(p2N, p2S);

    setActive(true);

    ActiveGame(p1, p2);

    return;

} //single sim constructor

Game::Game(string p1N, int p1S, int p2S){

    //Interactive Game

    Player p1(p1N, p1S);

    Player p2("AI", p2S);

    setActive(true);

    InterActiveGame(p1, p2);

    return;

} //interactive game constructor

Game::Game(string p1N, int p1S, string p2N, int p2S, bool turn_who){

    Player p1(p1N, p1S);

    Player p2(p2N, p2S);

    setActive(true);

    ActiveGameFlip(p1, p2);

    return;

} //multiple sim constuctor

//The different main game methods, Active game is used for the single sim and mutiple sim, InterActiveGame is used only in tyhe interactive part and activegameflip is for multiple sims

int Game::ActiveGame(Player& p1, Player& p2) {

    while (getActive() == true){

        //cout << endl << "P1: " << p1.getScore() << "P2: " << p2.getScore() << endl;

        setAPlayer(1);

        //cout << endl << "Player 1 Turn" << endl;

        int ExitCode = Turn(p1, p2);

        if (ExitCode != 10) {

            setAPlayer(2);

            //cout << endl << "Player 2 Turn" << endl;

            Turn(p2, p1);

        }

    }

    return 0;

}

int Game::InterActiveGame(Player& p1, Player& p2) {

    //Interactive Game

    while (getActive() == true){

        //cout << endl << "P1: " << p1.getScore() << "P2: " << p2.getScore() << endl;

        setAPlayer(1);

        //cout << endl << "Player 1 Turn" << endl;

        int ExitCode = InterTurn(p1, p2);

        if (ExitCode != 10) {

            setAPlayer(2);

            //cout << endl << "Player 2 Turn" << endl;

            VerboseTurn(p2, p1);

        }

    }

    return 0;

}

int Game::ActiveGameFlip(Player& p1, Player& p2) {

    while (getActive() == true){

        //cout << endl << "P1: " << p1.getScore() << "P2: " << p2.getScore() << endl;

        setAPlayer(2);

        //cout << endl << "Player 1 Turn" << endl;

        int ExitCode = Turn(p2, p1);

        if (ExitCode != 10) {

            setAPlayer(1);

            //cout << endl << "Player 2 Turn" << endl;

            Turn(p1, p2);

        }

    }

    return 0;

}

//different turn methods, turn is used in both single and multi sim, verbose and inter turn are used in the interactive game

int Game::Turn(Player& p, Player& p_other){

    int turn_throw = 0;

    for (int i=0; i < 3; i++){

        int temp_score = p.getScore();

        if (temp_score > 61){

            //Aim for tipple 20

            //cout << endl << "Aim for trip 20" << endl;

            turn_throw = p.throw_treble(20);

            temp_score = temp_score - turn_throw;

            if (EndTurnCheckNormal(temp_score, p, p_other) == 0){

                break;

            }

        }

        else if (temp_score <= 61 && temp_score >= 50){

            //Aim for Bullseye

            //cout << endl << "Aim for bullsye" << endl;

            turn_throw = p.throw_bull();

            temp_score = temp_score - turn_throw;

            int CheckResult = EndTurnCheckDB(temp_score, p, p_other);

            if (CheckResult == 0){

                break;

            }
            else if (CheckResult == 10){

                return 10;

            }

        }

        else if (temp_score < 50 && temp_score > 41){

            //Aim for double 20

            //cout << endl << "Aim for double 20" << endl;

            turn_throw = p.throw_double(20);

            temp_score = temp_score - turn_throw;

            if (EndTurnCheckNormal(temp_score, p, p_other) == 0){

                break;

            }

        }

        else if (temp_score == 1){

            //1 is remaining so player does nothing

            //cout << endl << "1 is remain so nothing done" << endl;

        }

        else if (temp_score < 40 && temp_score >= 23 && temp_score % 2 != 0){

            //Score is between 40 and 21 so player will try and get score under 21

            //cout << endl << "aim to get score under 21" << endl;

            int aim = temp_score / 2;

            aim = aim - 1;

            turn_throw = p.throw_double(aim);

            temp_score = temp_score - turn_throw;

            if (EndTurnCheckNormal(temp_score, p, p_other) == 0){

                break;

            }

        }

        else if(temp_score % 2 != 0){

            //Score is odd, so aim for (temp_score - 2)

            //cout << endl << "Aim to make score even" << endl;

            turn_throw = p.throw_single(temp_score-2);

            temp_score = temp_score - turn_throw;

            if (EndTurnCheckNormal(temp_score, p, p_other) == 0){

                break;

            }

        }

        else{

            //Aim for double to finish game

            //cout << endl << "Aim for double finish" << endl;

            turn_throw = p.throw_double(temp_score/2);

            temp_score = temp_score - turn_throw;

            int CheckResult = EndTurnCheckDB(temp_score, p, p_other);

            if (CheckResult == 0){

                break;

            }
            else if (CheckResult == 10){

                return 10;

            }

        }

    }

    return 0;

}

int Game::VerboseTurn(Player& p, Player& p_other){

    int turn_throw = 0;

    for (int i=0; i < 3; i++){

        int temp_score = p.getScore();

        if (temp_score > 61){

            //Aim for tipple 20

            cout << endl << "AI is aiming for for triple 20" << endl;

            turn_throw = p.throw_treble(20);

            cout << endl << "Ai Scored " << turn_throw << endl;

            temp_score = temp_score - turn_throw;

            if (EndTurnCheckNormal(temp_score, p, p_other) == 0){

                break;

            }

        }

        else if (temp_score <= 61 && temp_score >= 50){

            //Aim for Bullseye

            cout << endl << "AI aims for bullsye" << endl;

            turn_throw = p.throw_bull();

            cout << endl << "Ai Scored " << turn_throw << endl;

            temp_score = temp_score - turn_throw;

            int CheckResult = EndTurnCheckDB(temp_score, p, p_other);

            if (CheckResult == 0){

                break;

            }
            else if (CheckResult == 10){

                return 10;

            }

        }

        else if (temp_score < 50 && temp_score > 41){

            //Aim for double 20

            cout << endl << "AI Aims for double 20" << endl;

            turn_throw = p.throw_double(20);

            cout << endl << "Ai Scored " << turn_throw << endl;

            temp_score = temp_score - turn_throw;

            if (EndTurnCheckNormal(temp_score, p, p_other) == 0){

                break;

            }

        }

        else if (temp_score == 1){

            //1 is remaining so player does nothing

            cout << endl << "AI is at 1 and just throws dart at the wall lol" << endl;

        }

        else if (temp_score < 40 && temp_score >= 23 && temp_score % 2 != 0){

            //Score is between 40 and 21 so player will try and get score under 21

            int aim = temp_score / 2;

            aim = aim - 1;

            cout << endl << "AI aims for double" << aim << endl;

            turn_throw = p.throw_double(aim);

            cout << endl << "Ai Scored " << turn_throw << endl;

            temp_score = temp_score - turn_throw;

            if (EndTurnCheckNormal(temp_score, p, p_other) == 0){

                break;

            }

        }

        else if(temp_score % 2 != 0){

            //Score is odd, so aim for (temp_score - 2)

            cout << endl << "AI aims for single " << (temp_score-2) << endl;

            turn_throw = p.throw_single(temp_score-2);

            cout << endl << "Ai Scored " << turn_throw << endl;

            temp_score = temp_score - turn_throw;

            if (EndTurnCheckNormal(temp_score, p, p_other) == 0){

                break;

            }

        }

        else{

            //Aim for double to finish game

            cout << endl << "AI Aims for double " << (temp_score / 2) << endl;

            turn_throw = p.throw_double(temp_score/2);

            cout << endl << "Ai Scored " << turn_throw << endl;

            temp_score = temp_score - turn_throw;

            int CheckResult = EndTurnCheckDB(temp_score, p, p_other);

            if (CheckResult == 0){

                break;

            }
            else if (CheckResult == 10){

                return 10;

            }

        }

    }

    return 0;

}

int Game::InterTurn(Player& p, Player& p_other){

    int turn_throw = 0;

    for (int i=0; i < 3; i++){

        cout << endl << "Throw " << (i+1) << "/3 for this turn" << endl;

        int temp_score = p.getScore();

        int aim;

        bool valid1 = false;

        cout << endl << "The Score is You: " << temp_score << " vs The AI: " << p_other.getScore() << endl;
        cout << "Now please choose what field you would like to aim for (1-20, and 50 for bullseye): ";
        cin >> aim;

        while (valid1 == false) {

            if(aim == 50){

                valid1 = true;

            }
            else if(aim >=1 && aim <=20){

                valid1 = true;

            }
            else{

                cout << endl << "You have chosen invalid dart field, please try again (1-20, and 50 for bullseye): ";
                cin >> aim;

            }

        }

        if (aim >=1 && aim <=20){

            string aimtype;

            bool valid2 = false;

            cout << endl << "Please choose if you want to aim Single (S), Double (D) or Triple (T): ";
            cin >> aimtype;

            while (valid2 == false) {

                transform(aimtype.begin(), aimtype.end(), aimtype.begin(), ::tolower);

                if (aimtype == "s" || aimtype == "d" || aimtype == "t"){

                    valid2 = true;

                }
                else{

                    cout << endl << "You have chosen invalid aim type, please try again, Single (S), Double (D) or Triple (T): ";
                    cin >> aimtype;

                }

            }

            if (aimtype == "s"){
                //aim for single

                cout << endl << "Aiming for Single " << aim << endl;

                turn_throw = p.throw_single(aim);

                cout << endl << "You scored " << turn_throw << endl;

                temp_score = temp_score - turn_throw;

                if (EndTurnCheckNormal(temp_score, p, p_other) == 0){

                    break;

                }

            }

            else if(aimtype == "d"){
                //aim for double

                cout << endl << "Aiming for Double " << aim << endl;

                turn_throw = p.throw_double(aim);

                cout << endl << "You scored " << turn_throw << endl;

                temp_score = temp_score - turn_throw;

                int CheckResult = EndTurnCheckDB(temp_score, p, p_other);

                if (CheckResult == 0){

                    break;

                }
                else if (CheckResult == 10){

                    return 10;

                }


            }

            else{
                //aim for tripple

                cout << endl << "Aiming for Tripple " << aim << endl;

                turn_throw = p.throw_treble(aim);

                cout << endl << "You scored " << turn_throw << endl;

                temp_score = temp_score - turn_throw;

                if (EndTurnCheckNormal(temp_score, p, p_other) == 0){

                    break;

                }


            }


        }
        else if (aim == 50){

            cout << endl << "Aiming for Bullsye " << aim << endl;

            turn_throw = p.throw_bull();

            cout << endl << "You scored " << turn_throw << endl;

            temp_score = temp_score - turn_throw;

            int CheckResult = EndTurnCheckDB(temp_score, p, p_other);

            if (CheckResult == 0){

                break;

            }
            else if (CheckResult == 10){

                return 10;

            }

        }


    }

    return 0;

}

//These are two check fuctions that are used at the end of each throw to check if the user has 0 score or has gone below 0

int Game::EndTurnCheckDB(int temp_score, Player& p, Player& p_other){

    //cout << endl << "Player temp score " << temp_score << endl;

    if (temp_score == 0){

        //Player has 0 score

        //cout << endl << "Player has 0 score" << endl;

        p.setScore(temp_score);

        if (getAPlayer() == 1) {

            setActive(false);

            EndGame(p, p_other);


        }
        else{

            setActive(false);

            EndGame(p_other, p);

        }

        return 10;

    }

    else if (temp_score < 0 || temp_score == 1){

        //Player has gone below 0 and round is a bust

        //cout << endl << "Player has gone below 0 and round is a bust" << endl;

        return(0);

    }

    else{

        //Player has just normal turn and it will be deducted from total

        //cout << endl << "Player has just normal turn and it will be deducted from total" << endl;

        p.setScore(temp_score);

        return(1);

    }

}

int Game::EndTurnCheckNormal(int temp_score, Player& p, Player& p_other){

    //cout << endl << "Player temp score " << temp_score << endl;

    if (temp_score == 0){

        //Player has 0 score without bullseye or double, turn is a bust

        //cout << endl << "Player has 0 score without bullseye or double, turn is a bust" << endl;

        return(0);

    }

    else if (temp_score < 0 || temp_score == 1){

        //Player has gone below 0 and turn is a bust

        //cout << endl << "Player has gone below 0 and turn is a bust" << endl;

        return(0);

    }

    else{

        //Player has just normal turn and it will be deducted from total

        //cout << endl << "Player has just normal turn and it will be deducted from total" << endl;

        p.setScore(temp_score);

        return(1);

    }

}

//Fuction that ends the game and passes back tot he main.cpp

int Game::EndGame(Player& p1, Player& p2){

    //Ends the Game

    //cout << "Player 1 Score: " << p1.getScore() << endl;
    //cout << "Player 2 Score: " << p2.getScore() << endl;

    p1SetScore(p1.getScore());

    p2SetScore(p2.getScore());

    if (p1.getScore() == 0){

        setWinner(1);

    }
    else{

        setWinner(2);

    }


    return 0;

}

//setters and getters

bool Game::getActive() {

    return(active);

}

void Game::setActive(bool x) {

    active = x;

}

int Game::getAPlayer() {

    return(activePlayer);

}

void Game::setAPlayer(int x){

    activePlayer = x;

}

int Game::getWinner() {

    return(GameWinner);

}

void Game::setWinner(int x){

    GameWinner = x;

}

int Game::p1GetScore() {

    return(p1Score);

}

void Game::p1SetScore(int x){

    p1Score = x;

}

int Game::p2GetScore() {

    return(p2Score);

}

void Game::p2SetScore(int x){

    p2Score = x;

}