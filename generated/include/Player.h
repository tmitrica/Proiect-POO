#ifndef PLAYER_H
#define PLAYER_H

#include<iostream>
#include<string>

class Player {
    std::string name;
    int money, position, jail = 0;

public:
    explicit Player(const std::string &name = "", int money = 750, int position = 0, int jail = 0);

    void move(int pos);

    int move_train();

    void move_jail();

    int buy(int price);

    int getPosition() const;

    int getMoney() const;

    const std::string &getName() const;

    void ReceiveRent(int money);

    void PayRent(int money);

    int getJail() const;

    ~Player() = default;
};

#endif //PLAYER_H
