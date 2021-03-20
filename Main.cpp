#include "Board.hpp"
#include <cstdlib>
#include <iostream>
#include "Direction.hpp"
#include <array>
#include <ctime>

using namespace ariel;
using namespace std; 

/**
 * simple program to illustrate the Bulletin Board
 * first the board init with few posts into random cols and rows value 
 * then the user insert the method he want to use: 1 to post , 2 to read , 3 to show , any other number to exit
 */


int main() { 
const size_t default_size=8; // 8 posts
Board board;
string data;
int length,input;
array<string,default_size> posts{ "my_post","my dog has lost!","found iphone x!","need a job? call 111-111111", 
"need private teacher?","babysiter with 3 years of experience","found brown wallet","WANTED:Blone hair 20 years old man , bounty:1m$"};
 srand(time(NULL)); // to get random numbers
for(size_t i=0;i<default_size;i++){
    uint row,col;
    Direction random_d;
   
    
    row= rand()%30; // the row and col range is [0,29]
    col= rand()%30;
    if(col%2==0){random_d=Direction::Horizontal;} // if the col is even number the direction is Horizontal
    else{random_d=Direction::Vertical;}

    board.post(row,col,random_d,posts.at(i));
    
}

uint row,col,direction;
Direction d; 

while(true){
cout<<"to post press 1,to read press 2,to show press 3,somthing else to exit"<<endl;
cin>>input;
switch(input){

    case 1:
        cin.ignore();
        cout<<"please insert the data to post:"<<endl;
        std::getline(std::cin,data);
        cout<<"please choose row location (positive numbers):"<<endl;
        cin>>row;
        cout<<"please choose col location (positive numbers):"<<endl;
        cin>>col;
        cout<<"please choose Direction (1 for Horizontal, else Vertical"<<endl; 
        cin>>direction;
        if(direction==1){d=Direction::Horizontal;}
        else{d=Direction::Vertical;}
        board.post(row,col,d,data);
        break;

    case 2:
        cout<<"please insert the data length:"<<endl;
        cin>>length;
        cout<<"please choose row location (positive numbers):"<<endl;
        cin>>row;
        cout<<"please choose col location (positive numbers):"<<endl;
        cin>>col;
        cout<<"please choose Direction (1 for Horizontal, else Vertical"<<endl; 
        cin>>direction;
        if(direction==1){d=Direction::Horizontal;}
        else{d=Direction::Vertical;}
        cout<<board.read(row,col,d,length)<<endl;
        break;

    case 3:
        board.show();
        break;


    default:
        exit(0);
       
        
    }
}
    return 0; 
}