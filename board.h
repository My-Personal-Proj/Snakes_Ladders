#ifndef BOARD_H
#define BOARD_H

/*
    Includes of entities we are going to use here
*/
#include<string>
#include<cmath>
#include<vector>

// include the files we need for the board
#include "ladder.h"
#include "snake.h"
#include "player.h"
#include "tile.h"
using namespace std;

class Board{

    private:
        int n;
        int size;
        int numSnakes;
        int numLadders;
        int numPlayers;
        string config; // configuration of snakes and ladders by binary from

        bool isWon;
        bool isDraw;
        string WINNER="";

        

    
    public:

        vector<Player> players;
        vector<Tile> tiles;

        Board(int Size, int nPlayers, string config){
            n = sqrt(Size);
            size = Size;
            numPlayers = nPlayers;
            numSnakes = 0;
            numLadders = 0;
            isWon = false;
            // Setting tile positions
            for(int i = 1; i < size+1; i++ ){
                Tile t(i);
                tiles.push_back(t);
            }
            
            for(int i = 1; i < nPlayers +1; i++){
                Player p(i);
                players.push_back(p);
            }
        }

        void printBoard(){
            cout<< "\nTHESE ARE THE CURRENT PROPERTIES OF THIS BOARD\n";
            cout<< "-----------------------------------------------\n";
            cout<< "This board is of size: "<<size<< "\nAnd has dimesion: ("<< n <<" x "<< n <<" )\n";
            cout<< "The number of snakes is: "<<numSnakes<<endl;
            cout<< "The number of ladders is: "<<numLadders<<endl;
            cout<< "The number of players is: "<<numPlayers<<endl;
            cout<< "\n====================================================================================\n\n";
        }

        void addSnake(int pos, Snake snake){
            tiles.at(pos).setSnake(snake);
            numSnakes++;
        }

        void addLadder(int pos, Ladder ladder){
            tiles.at(pos).setLadder(ladder);
            numLadders++;
        }

        void setWinStatus(int winner){
            isWon = true;
            WINNER.append("w")
            .append(players.at(winner).getName());
        }
        void setIsDraw(){
            isDraw = true;
        }
        // Getters
        int getNumPlayers(){
            return numPlayers;
        }
        string getWinner(){
            return WINNER;
        }
        bool getIsDraw(){
            return isDraw;
        }
        int getSize(){
            return size;
        }

        bool getWinStatus(){
            return isWon;
        }
};



#endif
