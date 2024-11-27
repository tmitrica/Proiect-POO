#include "Property.h"

Property::Property(const std::string &name, const int price, const int rent, const int owned, Player *const owner) {
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
        return 2; /// visiting jail; start
    else if (price == 8)
        return 8; /// paid_parking;
    else if (price == 6)
        return 6; /// go_to_jail
    if (owned == 0 && player->buy(price)) {
        owned = 1;
        owner = player;
        return 1;
    } else if (owned == 0) {
        return 7;
    } else return 0;
} /// function to check if the property the player landed on is a special space (start, train station, jail, etc.)
/// if the property is unowned and the player has sufficient balance, it will be marked as owned by them


const std::string &Property::getName() const {
    return name;
} /// getter for the name, to identify the property on which a player landed

Player *Property::getOwner() const {
    return owner;
}

void Property::setOwned(const int local_owned) {
    this->owned = local_owned;
}

void Property::ApplyEffect(Player *player) const {
    std::cout << player->getName() << std::endl;
}

// Implementare "dummy" pentru funcția Display
void Property::Display() const {
    // Acest cod este inutil deoarece clasa Property este abstractă,
    // dar este necesar pentru vtable.
    std::cout << "This is a generic property. Should not be directly used.\n";
}

// Implementare pentru clone
Property* Property::clone() const {
    // Aruncă o eroare deoarece nu are sens să clonezi un obiect din clasa abstractă.
    throw std::runtime_error("Cannot clone an abstract Property object.");
}


int Property::getOwned() const {
    return owned;
}

void Property::setOwner(Player *local_owner = nullptr) {
    this->owner = local_owner;
}

int Property::getRent() const {
    return rent;
}
