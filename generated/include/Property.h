#ifndef PROPERTY_H
#define PROPERTY_H

#include<iostream>
#include<string>
#include "Player.h"

class Property {
protected:
    std::string name;
    int price, rent;
    int owned;
    Player *owner;

public:
    explicit Property(const std::string &name = "", int price = 0, int rent = 0, int owned = 0,
                      Player *owner = nullptr);

    virtual int buy(Player *player);

    virtual void ApplyEffect(Player *player) const;

    const std::string &getName() const;

    Player *getOwner() const;

    int getRent() const;

    void setOwned(int local_owned);

    int getOwned() const;

    void setOwner(Player *local_owner);

    virtual ~Property() = default; ///destructor
};
#endif //PROPERTY_H
