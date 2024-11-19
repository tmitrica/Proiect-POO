#include "Property.h"

Property::Property(const std::string &name, const int price, const int rent, const bool owned, Player *const owner) {
    this->name = name;
    this->price = price;
    this->rent = rent;
    this->owned = owned;
    this->owner = owner;
} /// parameterized constructor

int Property::buy(Player *player) {
    if (price == 3)
        return 3; /// community chest
    else if (price == 4)
        return 4; /// chance
    else if (price == 5)
        return 5; /// train station
    else if (price == 2)
        return 2; /// parking; visiting jail; start
    else if (price == 6)
        return 6; /// go_to_jail
    if (owned == false && player->buy(price)) {
        owned = true;
        owner = player;
        return 1;
    } else return 0;
} /// function to check if the property the player landed on is a special space (start, train station, jail, etc.)
/// if the property is unowned and the player has sufficient balance, it will be marked as owned by them

const std::string &Property::getName() const {
    return name;
} /// getter for the name, to identify the property on which a player landed
