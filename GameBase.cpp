//Rohan Sanghani Lab 4
// Reedham Kalariya Lab 4
// Arnav Awasthi Lab 4
// This is the .cpp file for the GameBase class. It contains the definitions of all of our member functions

#include "TicTacToeGame.h"
#include "GomokuGame.h"
#include <sstream>
#include <string>
using namespace std;

GameBase::GameBase(unsigned int x, unsigned int y) : wide(x), tall(y), player_x_turn(true), longest_display_string_length(max_length), board(vector<vector<string>>(x, vector<string>(y, ""))){

}

/*
Prompts user to enter coordinates. Coordinates are valid if they are within the bounds of board or if the position is already taken
*/
int GameBase::prompt(unsigned int& x, unsigned int& y) {
    std::cout << "Enter a coordinate or enter 'quit'" << std::endl;
    std::string coordinate;
    getline(std::cin, coordinate);

    //quits is user enters quit
    if (coordinate.compare("quit") == 0) {
        return user_quit;
    }
    //find the comma character in that string and store what comes before comma
    replace(coordinate.begin(), coordinate.end(), ',', ' ');
        //wrap the string in an istringstream
        std::istringstream iss (coordinate);
        //If the user inputs a string with the coordinate of a valid square on the board
        if(iss >> x && iss >> y){


            //check bounds first and second
            if(x>=minBound && x<=maxBound && y >= minBound && y <= maxBound){                   
                return success;
            } else if (x>=GminBound && x<=wide && y>=GminBound && y<=tall){
                return success;
            }
                //otherwise re prompt user
            else {
                return prompt(x, y);
            }
        }
        else {
            return prompt(x, y);
        }

    return prompt_fail;

}

/*
Play keeps record of whose turn it is and who to prompt whether the game was won or whether it was a draw
*/
int GameBase::play() {
    print();
    int num_turns = 0;
    while (true) {
        num_turns++;
        int result_turn = turn();
        //check all cases below of who won and if a user quit or game resulted in draw
        if (result_turn == user_quit) {
            return user_quit;
        }
        if (result_turn == game_draw) {
            std::cout << "Game resulted in a draw";
            return success;
        }
        if (result_turn == player_x_won) {
            std::cout << "Player X won";
            return success;
        }

        if (result_turn == player_y_won) {
            std::cout << "Player O won";
            return success;
        }

        if (result_turn == player_b_won) {
            std::cout << "Player B won";
            return success;
        }
        if (result_turn == player_w_won) {
            std::cout << "Player W won";
            return success;
        }


    }

}
/*
 Goal is to take arguments and if it's tic tac toe game, create TTT game object, if Gomoku, return Gomoku
*/
GameBase* GameBase::check_args(int argc, char* argv[]){
    //Tic Tac Toe, correct num args
    if (argc == expected_number_arguments_TTT && (strcmp(argv[fileName],"TicTacToe") == 0)) {
        GameBase* p = new TicTacToeGame();
        return p;
    }
    //Tic Tac Toe, incorrect number of args
    if (argc != expected_number_arguments_TTT && (strcmp(argv[fileName], "TicTacToe") == 0)) {
        //return a null pointer, then in main if it's null pointer, return error
        return nullptr;
    }
    //Gomoku, 2 args
    if (argc == expected_number_arguments_TTT && (strcmp(argv[fileName], "Gomoku") == 0)) {
        GameBase* p = new GomokuGame(gomoku_width, gomoku_height, gomoku_wins);
        return p;
    }
    //Gomoku, 3 args
    if (argc == expected_num_arg_withoutWinArg && (strcmp(argv[fileName], "Gomoku") == 0)) {
        string dim = argv[expected_number_arguments_TTT];

        std::istringstream iss2(dim);
        int d;
        iss2 >> d;
        //don't accept dimension less than 3
        if (d <= 0) {
            cout << "Nonpositive dimension entered" << endl;
            return nullptr;
        }

        if (d < expected_num_arg_withoutWinArg) {
            return nullptr;
        }
        else {
            GameBase* p = new GomokuGame(d, d, d);
            return p;
        }
    }
    //4 args
    if (argc == expected_number_arguments_G) {
        string dim = argv[expected_number_arguments_TTT];
        string match = argv[expected_num_arg_withoutWinArg];

        std::istringstream iss2(dim);
        unsigned int d;
        iss2 >> d;
        std::istringstream iss3(match);
        unsigned int m;
        iss3 >> m;
        if (d <= 0 || m<=0) {
            cout << "Nonpositive dimension or win number entered" << endl;
            return nullptr;
        }
        //don't allow dimensions or win amount less than 3
        if (d < expected_num_arg_withoutWinArg || m < expected_num_arg_withoutWinArg) {
            return nullptr;
        }
        if (d < m) {
            return nullptr;
        }
        if (d == expected_num_arg_withoutWinArg) {
            GameBase* p = new GomokuGame(d, d, m);
            return p;
        }
        if (d >= m) {
            GameBase* p = new GomokuGame(d, d, m);
            return p;
        }
        
    }
    return nullptr;
    }



