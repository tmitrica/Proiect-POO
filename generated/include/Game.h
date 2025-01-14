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

    template <typename T>
    void processSpecialProperty(Property &property, Player &player, GameLogger &logger, const std::string &propertyType) {
        if (auto *specialProperty = dynamic_cast<T *>(&property)) {
            logger.update(player.getName() + " at position " + std::to_string(player.getPosition()) +
                          " landed on a " + propertyType);
            specialProperty->ApplyEffect(&player);
        }
    }


  //  virtual void ApplyEffect();

    ~Game();
};

#endif //GAME_H
