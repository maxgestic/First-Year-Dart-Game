//
// Created by Max Ring on 25/03/2020.
//
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"

using namespace std;

void StartGame();
void StartSim();
void StartInterGame();

int main() {

	srand(time(NULL));

    bool menu_active=true;

    //system("CLS");

    while (menu_active == true) { //Starts the game menu giving the user options to either start a single sim, multiple sims, an interactive game or quit the program

        int menu_choice = 0;

        cout << "Welcome to the Simple Darts Game \nPlease choose one of the following options:\n1) Start Game\n2) Run Sim\n3) Ineractive Game\n4) Quit Game\nEnter your selection here: ";

        cin >> menu_choice;

        if (menu_choice == 1) {

            menu_active=false;
            StartGame(); //Will start single sim

        }

            else if (menu_choice == 2) {

                menu_active = false;
                StartSim(); //Will start multiple sim mode

            }

        else if (menu_choice == 3) {

                menu_active = false;
                StartInterGame(); //Will start interactive game mode

        }
        else if(menu_choice == 4){

            exit(0); //will quite program

        }

        else {

            cout << "\nYou have entered an invalid option please try again!"; //error chatching in case user enters invalid option

            system("CLS");

        }

    }
}

void StartGame(){

    system("CLS"); //Clear screen

    //Variable initialization

    string p1Name, p2Name;
    int p1Skill, p2Skill;

    //User input part, will ask for both players names and skills

    cout << "Please enter the name of Player 1: ";
    cin >> p1Name;
    cout << "\n\nPlease enter the Skill of player 1: ";
    cin >> p1Skill;

    system("CLS");

    cout << "Please enter the name of Player 2: ";
    cin >> p2Name;
    cout << "\n\nPlease enter the Skill of player 2: ";
    cin >> p2Skill;

    //Create instance of game and run simulation

    Game game(p1Name, p1Skill, p2Name, p2Skill);

    if (game.getWinner() == 1){

        //Player 1 Wins

        cout << endl << "Player 1 has won the game with " << game.p1GetScore() << endl << "Player 2 had a score of " << game.p2GetScore() << endl;

    }
    else{

        //Player 2 Wins

        cout << endl << "Player 2 has won the game with " << game.p2GetScore() << endl << "Player 1 had a score of " << game.p1GetScore() << endl;

    }

    //go back to main menu

    main();

}

void StartInterGame(){

    system("CLS"); //clears screen

    //variable initialization

    string p1Name;
    int p2Skill, p1Skill;

    //Asks user for their name and their darts skill and the the skill of the ai oponent

    cout << "Please enter your Name: ";
    cin >> p1Name;
    cout << "\n\nPlease enter your Darts Skill: ";
    cin >> p1Skill;

    system("CLS");

    cout << "\n\nPlease enter the AI Skill: ";
    cin >> p2Skill;

    //Will create instance of interactive game

    Game game(p1Name, p1Skill, p2Skill);

    if (game.getWinner() == 1){

        //Player 1 Wins

        cout << endl << "Player 1 has won the game with " << game.p1GetScore() << endl << "Player 2 had a score of " << game.p2GetScore() << endl;

    }
    else{

        //Player 2 Wins

        cout << endl << "Player 2 has won the game with " << game.p2GetScore() << endl << "Player 1 had a score of " << game.p1GetScore() << endl;

    }

    main();

}

void StartSim(){

    system("CLS");

    //variable initilization

    string p1Name, p2Name;
    int p1Skill, p2Skill, sim_number;

    //will ask the user for both players names and skill and then how many simulations they would like to run

    cout << "Please enter the name of Player 1: ";
    cin >> p1Name;
    cout << "\n\nPlease enter the Skill of player 1: ";
    cin >> p1Skill;

    system("CLS");

    cout << "Please enter the name of Player 2: ";
    cin >> p2Name;
    cout << "\n\nPlease enter the Skill of player 2: ";
    cin >> p2Skill;

    system("CLS");

    cout << "Please enter the amount of sims you'd like to run: ";
    cin >> sim_number;

    //creates array to store the different outcomes in (e.g. 0:7 is at index 0)

    int sim_array[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    //variable initialization

    int player1_OWins = 0, player2_OWins=0;

    int player_c = 1;

    //Runs simulation for the amount of times user specified
    for(int i = 0; i < sim_number; i++){

        //variable initialization

        //cout << "|";

        int p1_g_wins = 0, p2_g_wins = 0, game_winner = 0;

        //This loop is the game loop which will run up to a total of 13 times until one user has won 7 sets (best to 7)

        for(int game_loop = 0; game_loop < 13; game_loop++){

            //variable initialization

            int p1_s_wins = 0, p2_s_wins = 0, set_winner = 0;

            //This loop is the set loop it will run up to a total of 5 times until user has won 5 rounds (best to 3)

            for(int set = 0; set < 5; set++){

                int game_win_player;

                //This next if and else if statement is used to have alternating rounds of who goes first by changing the player_c to different states

                if (player_c == 1){

                    Game game(p1Name, p1Skill, p2Name, p2Skill);

                    game_win_player = game.getWinner();

                    player_c=2;

                }

                else if (player_c == 2){

                    Game game(p1Name, p1Skill, p2Name, p2Skill, true);

                    game_win_player = game.getWinner();

                    player_c=1;

                }

                if (game_win_player == 1){

                    //adds 1 round win to player 1

                    p1_s_wins++;

                }

                else{

                    //adds 1 round win to player 2

                    p2_s_wins++;

                }

                if(p1_s_wins == 3){

                    //checks if player 1 has 3 wins, if so will end the set and make player 1 the winner of the set

                    set_winner = 1;

                    break;

                } else if (p2_s_wins == 3){

                    //checks if player 2 has 3 wins, if so will end the set and make player 2 the winner of the set

                    set_winner = 2;

                    break;

                }

            } //End of Set loop

            if (set_winner == 1){

                //Player 1 Wins set

				//cout << endl << "Player 1 winns set" << endl;

                p1_g_wins++;

            }

            else{

                //Player 2 Wins set

				//cout << endl << "Player 2 winns set" << endl;

                p2_g_wins++;

            }

            if(p1_g_wins == 7){

                //checks if player 1 has 7 set wins, if so will end the set and make player 1 the winner of the game

                game_winner = 1;

                break;

            } else if (p2_g_wins == 7){

                //checks if player 2 has 7 set wins, if so will end the set and make player 2 the winner of the game

                game_winner = 2;

                break;

            }

        } //end of game loop

        if(game_winner == 1){

            player1_OWins++;

            //player 1 has won the game
            //the next switch statment is used to decide which index to increase in the array by checking player 2's score

            switch(p2_g_wins){

                case 0:
                    sim_array[13]++;
                    //cout << endl << "Adding 1 case of 7:0" << endl;
                    break;

                case 1:
                    sim_array[12]++;
                    //cout << endl << "Adding 1 case of 7:1" << endl;
                    break;

                case 2:
                    sim_array[11]++;
                    //cout << endl << "Adding 1 case of 7:2" << endl;
                    break;

                case 3:
                    sim_array[10]++;
                    //cout << endl << "Adding 1 case of 7:3" << endl;
                    break;

                case 4:
                    sim_array[9]++;
                    //cout << endl << "Adding 1 case of 7:4" << endl;
                    break;

                case 5:
                    sim_array[8]++;
                    //cout << endl << "Adding 1 case of 7:5" << endl;
                    break;

                case 6:
                    sim_array[7]++;
                    //cout << endl << "Adding 1 case of 7:6" << endl;
                    break;

            }

        }

        else{

            //player 2 has won the game
            //the next switch statment is used to decide which index to increase in the array by checking player 1's score

            player2_OWins++;

            switch(p1_g_wins){

                case 0:
                    sim_array[0]++;
                    //cout << endl << "Adding 1 case of 0:7" << endl;
                    break;

                case 1:
                    sim_array[1]++;
                    //cout << endl << "Adding 1 case of 1:7" << endl;
                    break;

                case 2:
                    sim_array[2]++;
                    //cout << endl << "Adding 1 case of 2:7" << endl;
                    break;

                case 3:
                    sim_array[3]++;
                    //cout << endl << "Adding 1 case of 3:7" << endl;
                    break;

                case 4:
                    sim_array[4]++;
                    //cout << endl << "Adding 1 case of 4:7" << endl;
                    break;

                case 5:
                    sim_array[5]++;
                    //cout << endl << "Adding 1 case of 5:7" << endl;
                    break;

                case 6:
                    sim_array[6]++;
                    //cout << endl << "Adding 1 case of 6:7" << endl;
                    break;

            }

        }


    } // end of sim loop

    //second array to store percentages in
    int percent_array[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    //next for loop is the maths of turing the indexes of the different scores into percentages

    for(int ree = 0; ree < 14; ree++){

        //cout << endl << ree << endl << sim_array[ree] << endl;

        double temp = (double)((double)sim_array[ree] / (double)sim_number) * 100;

        percent_array[ree] = (int)temp;

        //cout << endl << percent_array[ree] << endl;

    }

    cout << endl << "Simulation has concluded here are results: " << endl << "0 : 7 = " << percent_array[0] << "%" << endl << "1 : 7 = " << percent_array[1] << "%" << endl << "2 : 7 = " << percent_array[2] << "%" << endl << "3 : 7 = " << percent_array[3] << "%" << endl << "4 : 7 = " << percent_array[4] << "%" << endl << "5 : 7 = " << percent_array[5] << "%" << endl << "6 : 7 = " << percent_array[6] << "%" << endl << "7 : 6 = " << percent_array[7] << "%" << endl << "7 : 5 = " << percent_array[8] << "%" << endl << "7 : 4 = " << percent_array[9] << "%" << endl << "7 : 3 = " << percent_array[10] << "%" << endl <<  "7 : 2 = " << percent_array[11] << "%" << endl << "7 : 1 = " << percent_array[12] << "%" << endl << "7 : 0 = " << percent_array[13] << "%" << endl;

    cout << endl << "Player 1 won a total of " << player1_OWins << " times and Player 2 won a total of " << player2_OWins << " times.";

    Sleep(5000);

    //return to menu

    main();

}
