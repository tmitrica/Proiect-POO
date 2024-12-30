#include "Parking.h"

/**
 * @file Parking.cpp
 * @brief Implementation of the Parking class, a derived class from Property, representing the free parking tile.
 */

/**
 * @brief Constructs a Parking object with the specified name, price, and rent.
 *
 * @param name The name of the Parking property.
 * @param price The price of the property (not relevant for Parking).
 * @param rent The rent of the property (not relevant for Parking).
 */
Parking::Parking(const std::string &name, const int price, const int rent) : Property(name, price, rent) {
    this->name = name;
    this->price = price;
    this->rent = rent;
}

/**
 * @brief Applies the Parking effect to the specified player.
 *
 * @details The effect is that the player receives a bonus of 300. This simulates the player landing on a "Free Parking" space.
 *
 * @param player A pointer to the Player object that landed on the Parking space.
 */
void Parking::ApplyEffect(Player *player) const {
    player->buy(300);
    std::cout<<player->getName()<<" paid 300 for parking"<<"\n";
}
