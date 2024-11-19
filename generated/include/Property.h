#ifndef PROPERTY_H
#define PROPERTY_H

#include<iostream>
#include<string>
#include "Player.h"

class Property {
    std::string name;
    int price, rent;
    bool owned;
    Player *owner;

public:
    explicit Property(const std::string &name = "", const int price = 0, const int rent = 0, const bool owned = false,
                      Player *const owner = nullptr);

    int buy(Player *player);

    const std::string &getName() const;

    ~Property() = default; ///destructor
};
#endif //PROPERTY_H
