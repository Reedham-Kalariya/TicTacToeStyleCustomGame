// Rohan Sanghani Lab 4
// Reedham Kalariya Lab 4
// Arnav Awasthi Lab 4
// This is the .cpp file for the GomokuGame class. It contains the definitions of all of our member functions 
//

#include "GomokuGame.h"
using namespace std;

GomokuGame::GomokuGame(unsigned int wide, unsigned int tall, unsigned int args)
//this will initialize instance variables to be variables passed in
        :GameBase(wide, tall), win_number(args){
    //loop through vector and push back space to make all spaces empty
    for (unsigned int row = 0; row <= wide - offset; row++) {
        for (unsigned int col = 0; col <= tall - offset; col++) {
            board[row][col]=" ";
        }
    }
    widen = wide;
    match = args;
    string empty = " ";
    if (((int)empty.size() > (int)to_string(wide - offset).size())) {
        longest_display_string_length = empty.size();
    }
    else {
        longest_display_string_length = to_string(wide - offset).size();
    }
}

std::ostream& operator<<(std::ostream& x, const GomokuGame& y){
    
    int index_adjust = to_string(y.wide - offset).size();
    for(int row = y.wide - offset; row >= 0; --row){
        x << setw(index_adjust)<<row+ offset << " ";
        for(unsigned int col = 0; col < y.tall; ++col){
            x << setw(y.longest_display_string_length) << y.board[row][col] << ' ';
        }
        x << "\n";
    }
    x << setw(index_adjust) << " X ";
    for (unsigned int col = 0; col < y.tall; col++) {
        x << setw(y.longest_display_string_length) << col+ offset << " ";
    }
    x << "\n";
    return x;
}

bool GomokuGame::done(){
 
    //checking to see if we have a win in any of our rows
    int b_streak = 0;
    int w_streak = 0;
    for(unsigned int row = 0; row < wide; ++row){
        for(unsigned int col = 0; col < tall; ++col){
            if(board[row][col] == " "){
                b_streak = 0;
                w_streak = 0;
            }
            if(board[row][col] == "B"){
                b_streak += offset;
                w_streak = 0;
            }
            if(board[row][col] == "W"){
                b_streak = 0;
                w_streak += offset;
            }
            if(b_streak == win_number || w_streak == win_number){
                return true;
            }


        }
        b_streak = 0;
        w_streak = 0;
    }


    //checking to see if we have a win in any of our columns
    for(unsigned int row = 0; row < wide; ++row){
        for(unsigned int col = 0; col < tall; ++col){
            if(board[col][row] == " "){
                b_streak = 0;
                w_streak = 0;
            }
            if(board[col][row] == "B"){
                b_streak += offset;
                w_streak = 0;
            }
            if(board[col][row] == "W"){
                b_streak = 0;
                w_streak += offset;
            }
            if(b_streak == win_number || w_streak == win_number){
                return true;
            }
        }
        b_streak = 0;
        w_streak = 0;
    }


//First diag check

for (unsigned int x = 0; x < wide - match + offset; ++x) {
    for (unsigned int y = 0; y < tall - match + offset; ++y) {
        string previous = board[y][x];
        bool find_win = true;
        for (unsigned int i = 0; i < match; ++i) {
            if (board[y + i][x + i] != previous || board[y + i][x + i] == " ") {
                find_win = false;
                break;
            }
            previous = board[y + i][x + i];
        }
        if (find_win) {
            return true;
        }
        
    }

    }

//Second diag check


for (unsigned int x = 0; x < wide - match + offset; ++x) {
    for (unsigned int y = match - offset; y < tall; ++y) {
        string previous = board[y][x];
        bool find_win = true;

        for (unsigned int i = 0; i < match; ++i) {
            if (board[y - i][x + i] != previous || board[y - i][x + i] == " ") {
                find_win = false;
                break;
            }
            previous = board[y - i][x + i];
        }
        if (find_win) {
            return true;
        }
    }
}
    return false;


}

/*
This method takes no parameters. The game should remember which player's turn it is. The method
alternates whose turn it is each time it is called. The method calls the prompt() method to obtain valid coordinates for a valid
move in the game and determines whether or not the user has quit the game. If they have not quit the game, this method
places their piece on the coordinate and checks for a win or draw.
*/
int GomokuGame::turn() {
    player_w_turn = this->player_w_turn;
    //The game should remember which player's turn it is
    // assign this variable to false at the end to flip turns
    if (player_w_turn) {
        std::cout << "Enter a coordinate for your turn!" << std::endl;
        unsigned int x;
        unsigned int y;
        int prompt_resultX = prompt(x, y);
        //check if user quit
        if (prompt_resultX == user_quit) {
            return user_quit;
        }
        //check if we have valid coordinates
        if (prompt_resultX == success) {
            if (board[x- offset][y- offset] == " ") {
                //move piece to square
                board[x- offset][y- offset] = "W";
                std::cout << *this << std::endl;
                //check if we have a win after move is made
                if (done()) {
                    return player_w_won;
                }
                //check if we have a draw after move is made
                if (draw()) {
                    return game_draw;
                }
                //flip whose turn it is
                this->player_w_turn = false;
                
            }
        }
        return success;
    }
        //this will now be the case for Player B's turn - same code as above
    else {
        std::cout << "Enter a coordinate for your turn!" << std::endl;
        unsigned int x;
        unsigned int y;
        int prompt_resultY = prompt(x, y);
        if (prompt_resultY == user_quit) {
            return user_quit;
        }
        if (prompt_resultY == success) {
            if (board[x- offset][y- offset] == " ") {
                board[x- offset][y- offset] = "B";
                std::cout << *this << std::endl;
                if (done()) {
                    return player_b_won;
                    std::cout << "Player B wins" << std::endl;
                }
                if (draw()) {
                    return game_draw;
                    std::cout << "Draw" << std::endl;
                }
                this->player_w_turn = true;
                
            }
        }
        return success;
    }
}


/*
Checks if the game has resulted in a draw. This method takes no parameter and returns a boolean - true for draw and false for not a draw
*/
bool GomokuGame::draw(){
    
    //create copies of current board to predict possible moves for both players
    GomokuGame BFilledBoard = *this; //board for b
    GomokuGame WFilledBoard = *this; //board for w

    //iterate through entire board to check for empty spaces
    for(unsigned int row=0; row<wide; row++){
        for(unsigned int col=0;col<tall;col++){
            if(BFilledBoard.board[row][col] == " "){
                //if found empty space, add W to WFilledBoard for player w's turn and add B to BFilledBoard for player b's turn
                if (player_w_turn) {
                    WFilledBoard.board[row][col] = "W";
                }
                else {
                    BFilledBoard.board[row][col] = "B";
                }
                
               
            }
        }
    }
    //checks if there are possible wins in either board
    bool BResult = BFilledBoard.done();
    bool WResult = WFilledBoard.done();
    //if we do have possible wins for either board, return false because one of the players can still win
    if(BResult || WResult){
        return false;
    }
    return true;

}

//prints the board through ostream overloaded operator
void GomokuGame::print(){
    cout << *this << endl;
}
