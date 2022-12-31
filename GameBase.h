//Rohan Sanghani Lab 4
// Reedham Kalariya Lab 4
// Arnav Awasthi Lab 4
// This is our GameBase header file that declares our member variables for the GamBbase class
//

#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <memory>

enum dimensions { width = 5, height = 5, gomoku_width=19, gomoku_height=19, gomoku_wins = 5};
enum coordinates { low = 1, mid = 2, high = 3 };
enum bounds { minBound = 1, maxBound = 3, GminBound=1, GmaxBound=2};
enum { expected_number_arguments_TTT = 2, expected_num_arg_withoutWinArg = 3, expected_number_arguments_G = 4, progName = 0, fileName = 1};
enum {max_length = 0};
enum {offset = 1};


enum error_cases { success, failed_to_open, wrong_number_arguments, wrong_program_name, could_not_extract_dimension, could_not_read_line, failed_to_extract_piece, size_of_vector_no_match_gameboard, failed_to_read_pieces, user_quit, bad_memory_allocation, prompt_fail, user_entered_nonpos_dim };
enum results { player_x_won = 1, player_y_won = 2, player_b_won = 3, player_w_won=4, game_draw = 5 };

class GameBase{
public:
    GameBase(unsigned int, unsigned int);
    virtual bool done() = 0;
    virtual bool draw() = 0;
    virtual int prompt(unsigned int&, unsigned int&);
    virtual int turn() = 0;
    int play();
    virtual void print() = 0;
    static GameBase* check_args(int argc, char* argv[]);
protected:
    bool player_x_turn;
    bool player_w_turn;
    int longest_display_string_length;
    std::vector<std::vector<std::string>> board;
    unsigned int wide;
    unsigned int tall;
    unsigned int match;

};



