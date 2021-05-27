#include<iostream>
#include<ctime>

using namespace std;

int main(){

    // cout<< time(NULL)<<endl;

    srand(time(NULL));

    for(int i = 0; i < 10; i++){
        cout<< (rand()%6 )+1 << endl;
    }
}