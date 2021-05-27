#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<vector>
#include<cstdlib>
#include<ctime>

// including files that we need
#include "player.h"
#include "snake.h"
#include "ladder.h"
#include "board.h"

using namespace std;


// void createInputVec(vector<string> &vec , fstream input);   // input file to vector per line
void createBoards(vector<Board> boards, vector<string> inputFile); // creation of all boards from input file
bool isBoardInializer(char ch);
void split(vector<string> &vec, string str, string del);
int rollDice();

int main(){

    /* ---------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    fstream outputFile , inputFile; // creating input and output file 
    vector<vector<string>> inFile; // vector form of the input file

    outputFile.open("files/output.txt",ios::out);
    inputFile.open("files/inputfile.txt", ios::in);

    // Checking if the output file was created
    if(!outputFile){
        cout<< "Output file not created\n"; 
        return 1; // exit the program if creating output file failed
    }

    // Checking if the input file exist 
    if(!inputFile){
        cout<< "Input file Not Found\n";
        return 1; // exit the program if the file is not found
    }
    
     /*
        For the following while loop we insert the file lines into a vector
        This makes it easy for us to reference line by line
    */
    string line;
    while(true){
        vector<string> vec;
        getline(inputFile , line);
        if(inputFile.eof()){
            break;
        }
        if(line == "" || line == " ") continue;
        split(vec,line," ");

        inFile.push_back(vec);
    }
    
    /*----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    

    /*----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    // vector<Player> players;
    vector<Board> boards;
    int numPlayers;
    string binary;

    int boardIdx = 0; // Temporary board index for initializing indices

    /*
        This for loop puts the meat onto the bones we've created.
        It looks into the values of the input file and then create boards from the input file
        The boards are created and stored into a vector
        Each board can be seen as a game of it's own
    */
    for(int i = 0; i < inFile.size(); i++){
        
        // The if statement initializes our very first board
        // The function heavily relies on input format specified in the docs
        if(i == 0){
            vector<string> v = inFile.at(0); // read as the first line of the file

            // This if statement checks if the first line of the input file has the right parameters.
            if(v.size() != 4){
                cout<< "Your first line of input needs to have 4 strings"<< endl;
                return 1;
            }

            int boardSize = stoi(v.at(0));  // This line and the following 3 lines is extracting info about our first board
            numPlayers = stoi(v.at(1));
            string stNum = v.at(2);
            binary = v.at(3);
            Board board(boardSize, numPlayers, binary);
            boards.push_back(board);
            continue;
        }

        string s1 = inFile.at(i).at(0);
        string s2 = inFile.at(i).at(1);

        // This if statement checks whether your the current line initializes a new board or take parameters for a new board
        if(!isBoardInializer(s1.at(0))){
            vector<string> item;
            split(item,s2,"-");

            int itemPosition = stoi(item.at(0));
            int itemLength = stoi(item.at(1));
            if(s1 == "S"){
                Snake s(itemPosition, itemLength);
                boards.at(boardIdx).addSnake(itemPosition, s);
            }
            else if(s1 == "L"){
                Ladder l(itemPosition , itemLength);
                boards.at(boardIdx).addLadder(itemPosition,l);
            }
            else{
                cout<< "Line "<< i+1 << " of your input file's first letter needs to be ";
                cout << "capital 'S' for Snake paramenter of capital 'L' for the Ladder"<< endl;
                return 1;  
            }
        }
        else{
            // The if checks that the next board has proper initializations
            if(inFile.at(i).size() != 2){
                cout<< "Please check that your input parameters ";
                cout<< "for board number: "<< i+1 << "is entered correctly in you file" << endl;
                return 1;
            }
            // Do the right things here
            boardIdx ++;
            int boardSize = stoi(s1);
            numPlayers = stoi(s2);
            Board board(boardSize, numPlayers,binary);
            boards.push_back(board);
        }
    }

    /*---------------------------------------------------------------------------------------------------------------------------------------------------------------*/

    /*---------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    for(int i = 0; i < boards.size(); i++ )
    boards.at(i).printBoard();

    /*
        it's time to play the games
    */
    for(int j = 0; j < boards.size(); j++ ){

        Board *board = &boards.at(j);
        
        for(int k = 0; k < board->getNumPlayers(); k++){
            outputFile << board->players.at(k).getPlayerState()<<endl;
        }

        while(!board->getWinStatus()  && !board->getIsDraw()){
            for(int i = 0; i < board->getNumPlayers(); i++){
               Player *p =  &board->players.at(i);
                if(board->getIsDraw() || board->getWinStatus()) break;
                do{
                    p->rollDice();
                    
                    // check if the player is will surpass the winning position
                    if((p->getPosition() + p->getDice()) <=  board->getSize()){
                        p->setPlayerState(p->getDice() , "D",1);
                    }
                    else{
                        p->incrementCurrentRound();
                    }
                    outputFile<<p->getPlayerState()<<endl;
                    // check the current position for snake or ladder
                    if(board->tiles.at(p->getPosition()).getSnake().getStatus()){
                        p->setPlayerState(-board->tiles.at(p->getPosition()).getSnake().getLength() , "S",0);
                        outputFile<<p->getPlayerState()<<endl;
                    }
                    else if(board->tiles.at(p->getPosition()).getLadder().getStatus()){
                        p->setPlayerState(board->tiles.at(p->getPosition()).getLadder().getLength() , "L",0);
                        outputFile<<p->getPlayerState()<<endl;
                    }
                    if( p->getDice() == 6) p-> decrementCurrentRound();
                    
                }while(p->getDice() == 6);
                
            }

            if(board->getWinStatus()){
                outputFile<< board->getWinner()<<endl<<endl;
                break;
            }

            if(board->getIsDraw()){
                outputFile<<"D"<<endl<<endl;
                break;
            }

        }
    }

    inputFile.close();
    outputFile.close();
    return 0;
}




bool isBoardInializer(char ch){
    // check if the first letter if between 48 and 57 inclusive
    // return true if the condition is satisfied, return else otherwise
    if(int(ch) > 47 && int(ch) < 58)
        return true;
    
    return false;
}


/*
    The function below splits a string using a delimeter
    a delimeter is just a character we want to split the string by
    It stores them split in a vector we pass by reference
    Check out the difference between pass by value and pass by reference, so cool.
*/
void split(vector<string> &vec, string str, string del){
    int start = 0;
    int end = str.find(del);
    while(end != -1){
        vec.push_back(str.substr(start, end-start));
        start = end + del.size();
        end = str.find(del,start);
    }
    vec.push_back(str.substr(start, end-start));
}

int rollDice(){
    // srand(time(NULL));
    return  ((rand()%6)+1);
}

