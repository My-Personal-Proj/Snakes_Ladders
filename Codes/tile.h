#ifndef TILE_H
#define TILE_H

#include<iostream>
#include<vector>
#include<string>

#include "snake.h"
#include "ladder.h"

class Tile{
    private:
        Snake snake;
        Ladder ladder;
        int position;

        void setPosition(int pos){
            position = pos;
        }

    public:
        // constructor for no ladder and no snake
        Tile(int pos){
            setPosition(pos);
            
        }
        // constructor for snake
        Tile(int pos, Snake s){
            setPosition(pos);
            setSnake(s);
        }
        // constructor for ladder
        Tile(int pos, Ladder l){
            setPosition(pos);
            setLadder(l);
        }

        // Getters
        Snake getSnake(){
            return Tile::snake;
        }

        Ladder getLadder(){
            return Tile::ladder;
        }

        int getPosition(){
            return position;
        }

        // Setters

        void setSnake(Snake s){
            snake.set(s.getHead(), s.getLength());
        }

        void setLadder(Ladder l){
            ladder.set(l.getBase(), l.getLength());
        }

        
};

#endif