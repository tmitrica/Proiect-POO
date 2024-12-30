#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include "Observer.h"
#include <algorithm>
#include "GameLogger.h"

class Player {
    std::string name;
    int money, position, jail = 0, in_game;

    std::vector<Observer*> observers;

public:
    explicit Player(const std::string &name = "", int money = 750, int position = 0, int jail = 0, int in_game = 1);

    void move(int pos);
    void move_train();
    void move_jail();
    int buy(int price);

    int getPosition() const;
    int getMoney() const;
    const std::string &getName() const;
    void ReceiveRent(int local_money);
    void PayRent(int local_money);
    void setIn_Game(int local_in_game);
    int getIn_Game() const;
    int getJail() const;

    void addObserver(Observer* observer);

    ~Player() = default;
};

#endif //PLAYER_H
