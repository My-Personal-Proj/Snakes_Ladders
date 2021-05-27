#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<vector>

// including files that we need
#include "player.h"
#include "snake.h"
#include "ladder.h"
#include "board.h"

using namespace std;


// void createInputVec(vector<string> &vec , fstream input);   // input file to vector per line
void createBoards(vector<Board> boards, vector<string> inputFile); // creation of all boards from input file
bool isBoardInializer(string line);
void split(vector<string> &vec, string str, string del);


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
        split(vec,line," ");

        inFile.push_back(vec);
    }
    
    /*----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    
    vector<Player> players;
    vector<Board> boards;
    int numPlayers;

    int boardIdx = 0; // Temporary board index for initializing indices

    for(int i = 0; i < inFile.size(); i++){
        
        if(i == 0){
            vector<string> v = inFile.at(0);
            int boardSize = stoi(v.at(0));
            numPlayers = stoi(v.at(1));
            string stNum = v.at(2);
            string binary = v.at(3);
            Board board(boardSize, numPlayers, binary);
            boards.push_back(board);
            continue;
        }


        

    }

    inputFile.close();
    outputFile.close();
    return 0;
}




bool isBoardInializer(string line){
    // check if the first letter if between 48 and 57 inclusive
    // return true if the condition is satisfied, return else otherwise
    if(int(line[0])>48 && int(line[0])<58)
        return true;
    
    return false;
}

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


