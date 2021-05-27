#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include<cstdlib>
#include<ctime>
#include<iostream>

using namespace std;


class Player{
    private:
        int Position;   // player's current position
        int Dice;   // rolled die value
        int currentRound;
        int currentMoveAmount;
        string Name = "P-";    // Player Name
        string MoveStateSymbol; // state upon moving.. Either by die roll (D), Snake (S) or Ladder (L)
        string playerState = "";


    public:
        // constructor initializing the player
        Player(int name) {
            Name.append(to_string(name));
            Position = 0;
            currentRound = 0;
            Dice = 0;
            MoveStateSymbol = "D";
            playerState.append("R-").append("0").append(" ").append(Name).append(" D-").append("0").append(" M-").append("0"); 
        }

        /*
            Getters
        */
        string getPlayerState(){
            return playerState;
        }

        int getPosition(){
            return Position;
        }

        int getDice(){
            return Dice;
        }

        int getCurrentRound(){
            return currentRound;
        }

        int getcurrentMoveAmount(){
            return currentMoveAmount();
        }

        //MSS stands for Move State Symbol
        int setMoveStateSymbol(string MSS){
            MoveStateSymbol = MSS;
        }

        /*
            Setters
        */
        void setPlayerState(int moveAmount, string moveBy){
            currentMoveAmount = moveAmount;
            Position += moveAmount;
            
        }

        void setPosition(int pos){
            Position = pos;
        }

        void setDice(int d){
            Dice = d;
        }

        void setCurrentRound(int cR){
            currentRound = cR;
        }

        void setCurrentMoveAmount(int mA){
            currentMoveAmount = mA;
        }
        // Each player can roll their own 6 sided die
        void rollDie(){
            srand(time(0));
            Dice = (rand()%6)+1;
        }

};


#endif