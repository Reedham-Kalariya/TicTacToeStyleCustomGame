////Rohan Sanghani Lab 4
// Reedham Kalariya Lab 4
// Arnav Awasthi Lab 4
//This is our main.cpp file
#include "TicTacToeGame.h"
#include "GameBase.h"
using namespace std;

//Usage message function
int usage_message(char *name_program, string commandsAccepted){
    cout << commandsAccepted << endl;
    cout << "Usage: " << name_program << " <input_name>" << endl;
    cout << "If playing TicTacToe, no additional arguments are required and above command in message should suffice." << endl;
    cout << "If playing Gomoku, if no argument are mentioned, a Gomoku board of 19*19 with 5 tiles to match is created." << endl;
    cout << "If one argument of positive number larger than 3 is mentioned, a Gomoku game with board of that number*number with that number of tiles to match is created." << endl;
    cout << "Usage in Gomoku with 1 argument" << name_program << " <input_name>" << " Num_for_Board_Dimensions_and_tiles_to_match" << endl;
    cout << "If two arguments of 2 numbers larger than 3 is mentioned, a Gomoku game with board of number1*number1 with number2 of tiles to match is created." << endl;
    cout << "Usage in Gomoku with 2 arguments" << name_program << " <input_name>" << " Num_for_Board_Dimensions" << " tiles_to_match" << endl;
    return wrong_number_arguments;
}


int main(int argc, char* argv[]) {
    try{
        GameBase* q = GameBase::check_args(argc, argv);
        auto r = make_shared<GameBase*>(q);
        if(q == nullptr){
            string commandsAccepted = "Please enter the name of one of the valid games in the program in place of <input_name> as seen in next line: 1)TicTacToe 2)Gomoku";
            return usage_message(argv[progName], commandsAccepted);
        }
        else{
            return q->play();
        }

    }
    catch(bad_alloc){
        cout << "Failed to dynamically allocate memory" << endl;
        return bad_memory_allocation;
    }


}

//
