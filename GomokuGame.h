////Rohan Sanghani Lab 4
// Reedham Kalariya Lab 4
// Arnav Awasthi Lab 4
// This is our Gomoku game header file that contains declarations of our member functions

#pragma once

#include "GameBase.h"


class GomokuGame:public GameBase {
    friend std::ostream &operator<<(std::ostream&, const GomokuGame&);
public:
    GomokuGame(unsigned int, unsigned int, unsigned int);
    virtual void print();
    virtual bool done();
    virtual bool draw();
    virtual int turn();
private:
    int win_number;
    unsigned int widen;
    unsigned int match;
};

std::ostream& operator<<(std::ostream&, const GomokuGame&);





