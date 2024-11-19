#include "Player.h"

Player::Player(const std::string &name, const int money, const int position, const int jail) {
    this->name = name;
    this->money = money;
    this->position = position;
    this->jail = jail;
} /// parameterized constructor; players will start by default with $1500 and at position 0 (START), but we can change this if desired

void Player::move(const int pos) {
    if (position + pos >= 36) {
        std::cout << name << " collected 200$ by going over START\n";
        money += 200;
    }

    position = (position + pos) % 36;
} /// function to move on the board (considering the START space)

int Player::move_train() {
    if (position == 4) position = 12;
    else if (position == 12) position = 24;
    else if (position == 24) position = 32;
    else if (position == 32) {
        position = 4;
        money += 200;
        std::cout << "(collected 200$ from START)\n";
    }
    return position;
} /// function to move on the board using train stations

void Player::move_jail() {
    if (jail < 2) {
        position = 9;
        jail++;
        std::cout << name << " is in jail and cannot throw the dice\n";
    } else if (jail == 2) {
        jail = 0;
        std::cout << name << " can throw the dice again next round\n";
    }
} /// function to check if a player is in jail and how many turns they need to wait

int Player::buy(const int price) {
    if (price == 0) return 0;

    if (money >= price) {
        money -= price;
        return 1;
    } else return 0;
} /// function to check the balance when purchasing an unowned property

int Player::getPosition() const {
    return position;
}

const std::string &Player::getName() const {
    return name;
}

int Player::getJail() const {
    return jail;
}

/// getters for name, position, and the variable indicating if the current player is in jail or not

//Player::~Player() = default;/// destructor
