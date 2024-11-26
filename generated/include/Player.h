#ifndef PLAYER_H
#define PLAYER_H

#include<iostream>
#include<string>

class Player {
    std::string name;
    int money, position, jail = 0, in_game;

public:
    explicit Player(const std::string &name = "", int money = 750, int position = 0, int jail = 0, int in_game = 1);

    void move(int pos);

    int move_train();

    void move_jail();

    int buy(int price);

    int getPosition() const;

    int getMoney() const;

    const std::string &getName() const;

    void ReceiveRent(int money);

    void PayRent(int money);

    void setIn_Game(int in_game);

    int getIn_Game() const;

    int getJail() const;

    ~Player() = default;
};

#endif //PLAYER_H
