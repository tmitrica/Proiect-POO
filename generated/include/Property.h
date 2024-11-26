#ifndef PROPERTY_H
#define PROPERTY_H

#include<iostream>
#include<string>
#include "Player.h"

class Property {
    std::string name;
    int price, rent;
    int owned;
    Player *owner;

public:
    explicit Property(const std::string &name = "", int price = 0, int rent = 0, int owned = 0,
                      Player *owner = nullptr);

    int buy(Player *player);

    const std::string &getName() const;

    Player *getOwner() const;

    int getRent() const;

    void setOwned(int owned);

    int getOwned() const;

    void setOwner(Player *owner);

    ~Property() = default; ///destructor
};
#endif //PROPERTY_H
