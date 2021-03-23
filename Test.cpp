#include "doctest.h"
#include "Board.hpp"
#include <string>
#include <stdexcept>

using namespace ariel;
using namespace std;




/**
 * 7 test cases in total, each test case verify read and post 
 * 1 test case for exceptions 
 */

TEST_CASE("good post cases-Horizontal"){
    Board b;
    string data = "my_post";
    uint row=0, col=0;

    b.post(row,col,Direction::Horizontal,data); // simple check , post in (0,0) (row,col)
    CHECK(b.read(row,col,Direction::Horizontal,data.length()) == data);

    data="123", row=5 , col=3;
    b.post(row,col,Direction::Horizontal,data); // post in (5,3) 
    CHECK(b.read(row,col,Direction::Horizontal,data.length()) == data);

    data="!%*&^)", row=0 , col=1;
    b.post(row,col,Direction::Horizontal,data); // post in (0,1)
    CHECK(b.read(row,col,Direction::Horizontal,data.length()) == data);
    
    data="text with a lot of words and numbers 131246", row=8, col=2; // long text 
    b.post(row,col,Direction::Horizontal,data);
    CHECK(b.read(row,col,Direction::Horizontal,data.length()) == data);

}

TEST_CASE("good post cases-Vertical"){
    Board b;
    string data = "my_post";
    uint row=0, col=0;

    b.post(row,col,Direction::Vertical,data); // post (0,0)
    CHECK(b.read(row,col,Direction::Vertical,data.length()) == data);

    data="123", row=4 , col=3;
    b.post(row,col,Direction::Vertical,data); // row!=col
    CHECK(b.read(row,col,Direction::Vertical,data.length()) == data);

    data="!%*&^)", row=1 , col=1;
    b.post(row,col,Direction::Vertical,data); 
    CHECK(b.read(row,col,Direction::Vertical,data.length()) == data);

    data="text with a lot of words and numbers 131246", row=3, col=2;

     b.post(row,col,Direction::Vertical,data); // long text , vertical
     CHECK(b.read(row,col,Direction::Vertical,data.length()) == data);

}

TEST_CASE("test post with read-Horizontal"){
    Board b;
    string data= "my_post";
    uint row = 23 ,col = 31;

    b.post(row,col,Direction::Horizontal,data); 
    CHECK(b.read(row,col,Direction::Horizontal,data.length()) == data);

    data="123", row=5 , col=5 ; 
    b.post(row,col,Direction::Horizontal,data); 

    CHECK(b.read(row,col,Direction::Horizontal,data.length()) == data);

    data="!%*&^)", row=0 , col=0;  
    b.post(row,col,Direction::Horizontal,data); 

    CHECK(b.read(row,col,Direction::Horizontal,data.length()) == data);

    data="text with a lot of words and numbers 131246"; 
    b.post(row,col,Direction::Horizontal,data); 

    CHECK(b.read(row,col,Direction::Horizontal,data.length()) == data);

}

TEST_CASE("test post with read-Vertical"){
    Board b;
    string data= "my_post";
    uint row = 0 , col = 0;
    b.post(row,col,Direction::Vertical,data); 

    CHECK(b.read(row,col,Direction::Vertical,data.length()) == data);

    data="123", row=5 , col=5 ; 
    b.post(row,col,Direction::Vertical,data); 

    CHECK(b.read(row,col,Direction::Vertical,data.length()) == data);

    data="!%*&^)", row=0 , col=0; 
    b.post(row,col,Direction::Vertical,data); 

    CHECK(b.read(row,col,Direction::Vertical,data.length()) == data);

    data="text with a lot of words and numbers 131246"; 
    b.post(row,col,Direction::Vertical,data); 

    CHECK(b.read(row,col,Direction::Vertical,data.length()) == data);
    
}

TEST_CASE("read and post-Horizontal and Vertical"){
    Board b;
    string data = "Lost dog! - 013-3333333";
    uint row = 0, col = 0;
    b.post(row,col,Direction::Horizontal,data);
    CHECK(b.read(row,col,Direction::Horizontal,data.length()) == data);

    b.post(row,col,Direction::Vertical,data);
    CHECK(b.read(row,col,Direction::Horizontal,data.length()) == data);

    data = "found iphone x white 128 gb "; 

    b.post(row,col,Direction::Vertical,data);
    CHECK(b.read(row,col,Direction::Vertical,data.length())==data);

    b.post(row,col,Direction::Horizontal,data);
    CHECK(b.read(row,col,Direction::Horizontal,data.length()) == data);

    data = "need a vacation?"; 
    row = 3 , col = 12 ; 

    b.post(row,col,Direction::Horizontal,data);
    CHECK(b.read(row,col,Direction::Horizontal,data.length())==data);

    b.post(row,col,Direction::Vertical,data);
    CHECK(b.read(row,col,Direction::Vertical,data.length())==data);

    data = "babysiter with 3 years of expirence- 003-5690013";
    row=2, col= 2; 

    b.post(row,col,Direction::Vertical,data);
    CHECK(b.read(row,col,Direction::Vertical,data.length()) == data);

    b.post(row,col,Direction::Horizontal,data);
    CHECK(b.read(row,col,Direction::Horizontal,data.length())==data);
    
}


TEST_CASE("edge cases"){
    Board b;
    string empty;
    uint row = 0, col = 0;
    CHECK_THROWS(b.post(row,col,Direction::Horizontal,empty)); // cannot post empty string 
    CHECK_THROWS(b.post(row,col,Direction::Vertical,empty)); 
    


}


TEST_CASE("complex cases for read and post"){
    Board b; 
    string data = "hello",ans;
    uint row = 20 , col = 11 ;
    uint length = 5; 
    b.post(row,col,Direction::Horizontal,data);
    row = 20, col = 13;
    ans = "llo__";
    CHECK(b.read(row,col,Direction::Horizontal,length)==ans);
    data = "test for read";
    row=30, col = 50, length= 6;
    b.post(row,col,Direction::Vertical,data);
    row = 38;
    ans=" read_";
    CHECK(b.read(row,col,Direction::Vertical,length)==ans); 

    data ="the length of the string is 30";
    row= 0 , col= 0; 
    b.post(row,col,Direction::Horizontal,data);
    col = 29 ;
    length = 4;
    ans="0___" ;
    CHECK(b.read(row,col,Direction::Horizontal,length)==ans);

    data = "hello"; 
    row =20 ; 
    b.post(row,col,Direction::Vertical,data);
    row=22;
    ans="llo___";
    length=6;
    CHECK(b.read(row,col,Direction::Vertical,length)==ans);
    row = 100, col= 0 ; 

    ans= "______";//length=6
    CHECK(b.read(row,col,Direction::Horizontal,length)==ans);
    CHECK(b.read(row,col,Direction::Vertical,length)==ans);
    row = 0 , col = 100 ;
    CHECK(b.read(row,col,Direction::Horizontal,length)==ans);
    CHECK(b.read(row,col,Direction::Vertical,length)==ans);

    row = 100 ; 
    CHECK(b.read(row,col,Direction::Horizontal,length)==ans);
    CHECK(b.read(row,col,Direction::Vertical,length)==ans);
    data= "h", ans = "h";
    length=1;
    b.post(row,col,Direction::Vertical,data); 
    CHECK(b.read(row,col,Direction::Vertical,length)==ans);
    CHECK(b.read(row,col,Direction::Horizontal,length)==ans);
    row=101,col=101;
    ans= "_"; 
    CHECK(b.read(row,col,Direction::Vertical,length)==ans);
    CHECK(b.read(row,col,Direction::Horizontal,length)==ans);

}

// //optional 
// TEST_CASE("illustrate show"){
//     Board b;
//     string data= "lost dog!- please help!!- phone number 011-333231332"; 
//     uint row=0,col=0; 
//     b.post(row,col,Direction::Horizontal,data);
//     col = 3;
//     b.post(row,col,Direction::Vertical,data);
   
//     data= "found iphone x ! black 128gb";
//     row = 5, col = 3 ;
//     b.post(row,col,Direction::Horizontal,data); 

//     b.post(row,col,Direction::Vertical,data);
//     data = "need private teacher ?  call 011-33332213"; 
//     row= 10, col = 6; 
//     b.post(row,col,Direction::Vertical,data);

//     row=7,col=12; 
//     b.post(row,col,Direction::Horizontal,data);
//     data = "more information"; 
//     row= 9, col= 5; 
//     b.post(row,col,Direction::Vertical,data);
//     row= 40, col= 4; 
//     b.post(row,col,Direction::Vertical,data);
//     row= 60, col= 8; 
//     b.post(row,col,Direction::Vertical,data);
//      row= 80, col= 50; 
//     b.post(row,col,Direction::Vertical,data);
//      b.post(row,col,Direction::Vertical,data);
//     row= 20, col= 80; 
//     b.post(row,col,Direction::Vertical,data);
//      row= 12, col= 20; 
//     b.post(row,col,Direction::Vertical,data);

//     b.show();
// }
