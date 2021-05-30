// 2321753
#ifndef SNAKE_H
#define SNAKE_H

using namespace std;
class Snake{

    private:
        int Head;
        int Tail;
        int Length;
        bool status;

    public:
        Snake(){
            Head = 0;
            Length = 0;
            Tail = 0;
            status = false;
        }

        Snake(int head, int length){
            setHead(head);
            setLength(length);
            status = true;
            if((head - length) < 0)
                setTail(0);
            else
                setTail(head-length);
        }

        int getLength(){
            return Length;
        }

        int getHead(){
            return Head;
        }

        int getTail(){
            return Tail;
        }

        bool getStatus(){
            return status;
        }

        // setters

        void set(int head, int len){
            Head = head;
            Length = len;
            Tail = head - len;
            status = true;
        }


        void setLength(int len){
            Length = len;
        }

        void setTail(int t){
            Tail = t;
        }

        void setHead(int h){
            Head = h;
        }


};



#endif