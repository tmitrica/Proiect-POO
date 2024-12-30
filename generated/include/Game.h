#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<string>
#include<fstream>
#include "Board.h"

class Game {
    protected:
    Player *players;
    int players_number = 0;
    Board board;
    GameLogger logger;

public:

    Game(const std::string &f, const std::string &g);

    void PrintProperties() const;

    void RemovePlayer(int currentPlayer);

    int Turn(int currentPlayer, int turn);

  //  virtual void ApplyEffect();

    ~Game();
};

#endif //GAME_H
