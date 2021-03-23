#include "Board.hpp"
#include <string>
#include <vector> 
#include <stdexcept>


using namespace std;
using namespace ariel;


/**
 * This class represents Bulletin Board , it support methods like post and read , 
 * each method attached with explanations . 
 */

     //constructor - init the panel (2D array) to default size . 

     Board::Board():INIT_SIZE(2) {
         this->rows=2; 
         this->cols=2;
         this->DEFAULT='_'; // this char is the default value for the array

         for(int i=0;i<INIT_SIZE;i++){
             vector<char> temp(this->INIT_SIZE);// create array of chars 
             for(int j=0;j<INIT_SIZE;j++){
                 temp.push_back(this->DEFAULT); // init the array to the default value 
             }
             this->panel.push_back(temp); // add the array
         }
     } 

     //destructor
     Board::~Board(){ } 
    //      for(int i=0;i<this->rows;i++){
    //          delete[] this->panel.at(i);
    //      }
    //      delete[] this->panel;
    //  }

    //getters
    std::vector<std::vector<char>> Board::get_panel() const{
        return this->panel;
    }

    uint Board::get_rows() const{
        return this->rows;
    }

    uint Board::get_cols() const{
        return this->cols;
    }

    //setters
    void Board::set_rows(uint row){
        this->rows=row;
    }

    void Board::set_cols(uint col){
        this->cols=col;
    }

    //methods 
  
    /**
     * post the given data into the board
     * depends on the given direction
     * if the row/col is bigger then the array size the array size will increased . 
     */
    void Board::post_data(string data,Direction direction,uint row,uint col){
        string::iterator it = data.begin();// iterate the data 

         if(direction==Direction::Horizontal){
             for(int i=0;i<data.length();i++){
                 this->panel.at(row).at(col++)=(*it.base());
                 it++;}
         }
         else{
             for(int i=0;i<data.length();i++){
                 this->panel.at(row++).at(col)=(*it.base());
                 it++;}
         }
    }
    /**
     * main method - post the given data in the specific row and col. 
     * if the row/col is bigger then the array size the array size will increased .
     * 
     */
     void Board::post(uint row,uint col,Direction direction,string const& data){
        
        resize_matrix(row,col);// if the row or col is out of bondes then the matrix will be resized 
        
        // make sure there is enough space to post the data 
        if(has_space(data.length(),direction,row,col)){//there is enough space.

             post_data(data,direction,row,col);// post the data
        }
        else{ // there is no enough space to post - need to resize 
    
            if(direction==Direction::Horizontal){//the resize value depends on the direction
                size_t value = calculate_resize(data.length(),col,direction);// calculate how much needed to resize
        
                for(size_t i=0;i<this->rows;i++){
                    this->panel.at(i).resize(value,this->DEFAULT);// resize the matrix 
                 }
                set_cols(value);
            
                post_data(data,direction,row,col);// there is enough space -> now we can post the data       
            }
            else{ // the direction is Vertical
            size_t value = calculate_resize(data.length(),row,direction);

         
                this->panel.resize(value,vector<char>(this->cols,this->DEFAULT));
                set_rows(value);
           // }//there is enough space, 
            post_data(data,direction,row,col);
        }
     }
 }
    
    /**
     * return the string that represents the posted data , 
     * if the row/col is bigger then the array size then the data will increase with the 
     * default value. 
     */
    string Board::read(uint row,uint col,Direction direction,uint length){
        string data;
        //input check 
        if(length<0){throw std::out_of_range{"the post length cant be negative!"};}
        //make sure row and col is smaller then the array size 
        if(row>=this->rows||col>=this->cols){
            for(int i=0;i<length;i++){
                data+=this->DEFAULT;
            }
            return data;
        }
        //read the data 
        if(direction==Direction::Horizontal){
            for(int i=0;i<length;i++){
                if(col>=this->cols){data+=this->DEFAULT;// out of the array bondes
                continue;//add only the default value 
                }
                data+= this->panel.at(row).at(col++);}
        }
        else{// the direction is Vertical 
            for(int i=0;i<length;i++){
                if(row>=this->rows){data+=this->DEFAULT; // out of the array bondes
                continue;
                }
                data+= this->panel.at(row++).at(col);}
        }
       return data;
    }

    /**
     * show the Bulletin Board , each line is printed with her number . 
     * 
     */
    void Board::show(){
        for(size_t i=0;i<this->rows;i++){
            cout<<'\t'<<i<<":";
            for(size_t j=0;j<this->cols;j++){
                cout<<this->panel.at(i).at(j);}
                     cout<<endl;
                     }
                     cout<<endl;
    }

    /**
     * This method return true iff there is enough space to post all the data 
     */

    bool Board::has_space(int post_length,Direction direction,uint row,uint col) const{
        bool ans = false;

        if(this->rows<row||this->cols<col){return ans;}
        if(direction == Direction::Horizontal){
            if(this->cols<col+((uint)post_length)){return ans;}// there is no enough space 
            ans= true;}
        else{
            if(this->rows<row+((uint)post_length)){return ans;}
            ans= true; 
        }
        return ans; 
    }

     /**
      * This method calculate the value that should be resized , depends on the given direction 
      */ 

     size_t Board::calculate_resize(uint post_length,uint start_position,Direction direction)const{
        size_t ans=0;
        
        //size_t sum=post_length+start_position; 
        if(direction == Direction::Horizontal){ 
        size_t diff = this->cols-start_position;
        ans=this->cols+post_length-diff;
        }
        else{
            size_t diff = this->rows-start_position;
            ans=this->rows+post_length-diff;
        }
        return ans;
    }   

    /**
     * resize the matrix if the row or col is out of the array bondes 
     */
    void Board::resize_matrix(uint row,uint col){
        
        if(row>this->rows){
            this->panel.resize(row+1,vector<char>(this->cols,this->DEFAULT));   
            set_rows(row+1);
        }
        if(col>this->cols){
            for(size_t i=0;i<this->rows;i++){
                this->panel.at(i).resize(col+1,this->DEFAULT);
            }
            set_cols(col+1);
        }
    }

    


