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

        vector<Snake> snakes;
        vector<Ladder> ladders;
        vector<Player> players;
        vector<Tile> tiles;

    
    public:
        Board(int Size, int nPlayers, string config){
            n = sqrt(Size);
            size = Size;
            numPlayers = nPlayers;

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

        void addSnake(int pos, Snake snake){
            tiles.at(pos).setSnake(snake);
        }

        void addLadder(int pos, Ladder ladder){
            tiles.at(pos).setLadder(ladder);
        }

};



#endif
