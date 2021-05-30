// 2321753
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
            srand(time(NULL));
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

        string getName(){
            return Name;
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
            return currentMoveAmount;
        }

        //MSS stands for Move State Symbol
        void setMoveStateSymbol(string MSS){
            MoveStateSymbol = MSS;
        }

        /*
            Setters
        */
        void setPlayerState(int moveAmount, string moveBy , int inc){
            currentMoveAmount = moveAmount;
            Position += moveAmount;
            MoveStateSymbol = moveBy;
            if(inc != 0) incrementCurrentRound();
            playerState = "";
            playerState.append("R-")
            .append(to_string(currentRound))
            .append(" "+Name);
            
            if(moveBy == "S")
                playerState.append(" "+moveBy);
            else
                playerState.append(" "+moveBy+"-");

            playerState.append(to_string(moveAmount))
            .append(" M-")
            .append(to_string(Position));

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
            Dice = int(rand()%6+1)%6 + 1;
        }

        void setDie(int n){
            Dice = n;
        }
        void incrementCurrentRound(){
            currentRound++;
        }
        void decrementCurrentRound(){
            currentRound--;
        }

};


#endif