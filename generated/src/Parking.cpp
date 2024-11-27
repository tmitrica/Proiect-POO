#include "Parking.h"

Parking::Parking(const std::string& name, const int price, const int rent) {
  this->name = name;
  this->price = price;
    this->rent = rent;
}

void Parking::ApplyEffect(Player *player) const {
    std::cout<<player->getName()<<" landed on the paid parking space and pays a fee of 300\n";
    player->buy(300);
}
