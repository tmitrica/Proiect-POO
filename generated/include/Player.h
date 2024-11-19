#ifndef PLAYER_H
#define PLAYER_H

#include<iostream>
#include<string>

class Player {
    std::string name;
    int money, position, jail = 0;

public:
    explicit Player(const std::string &name = "", const int money = 1500, const int position = 0, const int jail = 0);

    void move(const int pos);

    int move_train();

    void move_jail();

    int buy(const int price);

    int getPosition() const;

    const std::string &getName() const;

    int getJail() const;

    ~Player() = default;
};

#endif //PLAYER_H
