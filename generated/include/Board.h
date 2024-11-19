#ifndef BOARD_H
#define BOARD_H

#include<iostream>
#include<string>
#include<fstream>
#include "Property.h"

class Board {
    Property *properties;

public:
    explicit Board(const std::string &f);

    const Property &getProperty(const int position) const;

    friend void Turn(int currentPlayer, Player *players, const Board &board);

    ~Board();
};

#endif //BOARD_H
