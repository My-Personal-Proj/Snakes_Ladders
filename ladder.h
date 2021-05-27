#ifndef LADDER_H
#define LADDER_H

#include<string>

using namespace std;

class Ladder{
    private:
        int base;
        int length;
        int end;
        bool status;

    public:
        // Constructor

        Ladder(){
            base = 0;
            length = 0;
            end = 0;
            status = false;
        }

        Ladder(int Base, int len){
            setBase(Base);
            setLength(len);
            setEnd(Base + len);
            status = true;
        }


        // Getters
        int getBase(){
            return base;
        }

        int getLength(){
            return length;
        }

        int getEnd(){
            return end;
        }

        bool getStatus(){
            return status;
        }

        // Setters
        void set(int b , int len){
            status = true;
            base = base;
            length = len;
            end = base + len;
        }

        void setBase(int b){
            base = b;
        }

        void setLength(int l){
            length = l;
        }

        void setEnd(int e){
            end = e;
        }


};


#endif