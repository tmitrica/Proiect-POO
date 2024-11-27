#include "Parking.h"

Parking::Parking(const std::string &name, const int price, const int rent):Property(name, price, rent) {
    this->name = name;
    this->price = price;
    this->rent = rent;
}

void Parking::ApplyEffect(Player *player) const {
    player->buy(300);
}

