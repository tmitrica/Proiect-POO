#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<string>
#include<fstream>
#include "Board.h"

class Game {
    Player *players;
    int players_number = 0;
    Board board;

public:
    explicit Game(const std::string &f, const std::string &g);

    void Turn(int currentPlayer) const;

    friend std::ostream &operator<<(std::ostream &os, const Game &obj);

    ~Game();
};

#endif //GAME_H
