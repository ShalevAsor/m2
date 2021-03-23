#pragma once 
#include "Direction.hpp"
#include <iostream>
#include <vector>

namespace ariel{

    class Board{
    
    private:

        std::vector<std::vector<char>> panel; 
        uint rows;
        uint cols;
        const uint INIT_SIZE;
        char DEFAULT;


        bool has_space(int post_length,Direction direction,uint row,uint col)const;
        
        void post_data(std::string data,Direction direction,uint row,uint col);

        void res(size_t value,uint sp,Direction d);

        size_t calculate_resize(uint post_length,uint start_position,Direction direction)const;

        void resize_matrix(uint row,uint col);

    public:
        //constructors
        Board(); 

        //destructos
        ~Board();


        //getters
        std::vector<std::vector<char>> get_panel() const;
        uint get_rows() const;
        uint get_cols() const;

        //setters
        void set_rows(uint row);
        void set_cols(uint col);
        

        //tostring
        std::string to_string();

        //methods
        void post(uint row,uint col,Direction direction,const std::string &data);

        std::string read(uint row,uint col,Direction direction,uint length);

        void show();

    };


};