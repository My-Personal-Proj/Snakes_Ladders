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

int main(){


    /* This section reads in all the lines from the input file and stores results into a vector*/
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
    
    /*This section initializes all the boards for us*/
    /*The initialization includes, number of players, board size, snakes and ladders too of every board*/
    /*Each board is then sored into a vector of boards*/
    /*----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    vector<Board> boards;
    int numPlayers;
    string binary;
    string stdNum;

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
            stdNum = v.at(2);
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

    /* Now that every board is initialized, This section here plays the game and writes every thing into the output file*/
    /*---------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    
    /*
        it's time to play the games
    */
    for(int j = 0; j < boards.size(); j++ ){
        // For every single board, do what's below

        if(j == 0){
            // First line of input into the file
            outputFile << boards.at(j).getSize()<<" " <<stdNum <<" "<<binary<<endl; 
        }else // first line of input for every new board
            outputFile << boards.at(j).getSize()<<endl;

        // Creating a reference to the current board    
        Board *board = &boards.at(j);
        
        /* THis is for debugging purposes*/
        for(int k = 0; k < board->getNumPlayers(); k++){
            outputFile << board->players.at(k).getPlayerState()<<endl;
        }
    
        // Playing the game for as long no winner has been found and the for as long as it's not a draw
        while(!board->getWinStatus()  && !board->getIsDraw()){
            // give every player a chance to play the game
            for(int i = 0; i < board->getNumPlayers(); i++){
                // create a player reference in the current game
                Player *p =  &board->players.at(i);

                // Check the current state of the board for any winners or end of game with a draw
                board->checkBoardState();
                if(board->getWinStatus() || board->getIsDraw()) break;
                
                // The do while loop let's a player play for as long as they are rolling 6's
                // Trust me this works wonders
                do{
                    p->rollDie(); 
                    
                    // check if the player is will surpass the winning position
                    // Move only if the move doesn't go beyond the size of the board
                    if((p->getPosition() + p->getDice()) <=  board->getSize()){
                        // The line below handles it all for us
                        p->setPlayerState(p->getDice() , "D",1);
                    }
                    else{
                        // increment the round the player is currently in
                        p->incrementCurrentRound();
                    }
                    // Write current move of player by Die Roll
                    outputFile<<p->getPlayerState()<<endl;

                    // Check for a win upon a move
                    board->checkBoardState();
                    if(board->getWinStatus() || board->getIsDraw()) break;

                    // check the current position for snake or ladder
                    if(board->tiles.at(p->getPosition()).getSnake().getStatus()){
                        p->setPlayerState(-board->tiles.at(p->getPosition()).getSnake().getLength() , "S",0);
                        outputFile<<p->getPlayerState()<<endl;  
                        /*No need to check here because we cannot win by being bitten by a snake*/
                    }
                    else if(board->tiles.at(p->getPosition()).getLadder().getStatus()){
                        // Move up a ladder if you current position is a ladder
                        p->setPlayerState(board->tiles.at(p->getPosition()).getLadder().getLength() , "L",0);
                        outputFile<<p->getPlayerState()<<endl;

                        /* Since we've moved up, Check for any potential wins and losses*/
                        board->checkBoardState();
                        if(board->getWinStatus() || board->getIsDraw()) break;
                    }

                    // mechanism for controlling the current round a player is in
                    // trust it works coz it does
                    if( p->getDice() == 6) p-> decrementCurrentRound();
                    
                }while(p->getDice() == 6); // loop controller for any move
                
            }

            /*If a winner has been found, add winner line appropriately*/
            if(board->getWinStatus()){
                outputFile<< board->getWinner()<<endl<<endl;
                break;
            }

            /* If the game ended and there's no winner, leave it at that*/
            if(board->getIsDraw()){
                outputFile<<"D"<<endl<<endl;
                break;
            }

        }
    }

    /*Close the openend files*/
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

