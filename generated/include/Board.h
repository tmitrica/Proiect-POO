#ifndef BOARD_H
#define BOARD_H

#include<iostream>
#include<string>
#include<fstream>
#include "Property.h"
#include "Chest.h"
#include "Chance.h"
#include "Parking.h"
#include<vector>

class Board {
    std::vector<Property *> properties;
    static int properties_count;

public:
    explicit Board(const std::string &f);

    static int getProperties_count();

    Property &getProperty(int position) const;

    friend void Turn(int currentPlayer, Player *players, const Board &board);

    ~Board();
};

#endif //BOARD_H
