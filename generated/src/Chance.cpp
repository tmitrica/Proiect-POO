#include "Chance.h"

/**
 * @file Chance.cpp
 * @brief Implementation of the Chance class, a derived class from Property, which applies random effects to players.
 */

/**
 * @brief Constructs a Chance object with the specified name, price, and rent.
 *
 * @param name The name of the Chance property.
 * @param price The price of the property.
 * @param rent The rent of the property (not used in Chance effects).
 */
Chance::Chance(const std::string &name, const int price, const int rent) : Property(name, price, rent) {
    this->name = name;
    this->price = price;
    this->rent = rent;
}

/**
 * @brief Applies a random effect to the specified player.
 *
 * @details The effect is chosen randomly from 10 possible outcomes:
 * - **0:** Player pays 500 for taxes.
 * - **1:** Player receives 150 for income.
 * - **2:** Player moves to the START position.
 * - **3:** Player moves forward 3 spaces.
 * - **4:** Player moves backward 3 spaces.
 * - **5:** Player goes to Jail.
 * - **6:** Player moves to the first train station.
 * - **7:** Player moves backward 5 spaces.
 * - **8:** Player moves to property number 20.
 * - **9:** No effect ("nothing happens").
 *
 * @param player A pointer to the Player object affected by the chance card.
 */

void Chance::ApplyEffect(Player *player) const {
    int action = rand() % 10; ///< Randomly generating an action.

    if (action == 0) {
        std::cout << player->getName() << " pays 500 for taxes\n";
        player->buy(500);
    } else if (action == 1) {
        std::cout << player->getName() << " receives 150 for income\n";
        player->buy(-150);
    } else if (action == 2) {
        std::cout << player->getName() << " moves to START\n";
        player->move(36 - player->getPosition());
    } else if (action == 3) {
        std::cout << player->getName() << " moves forward 3 spaces\n";
        player->move(3);
    } else if (action == 4) {
        std::cout << player->getName() << " moves backward 3 spaces\n";
        player->move(33);
    } else if (action == 5) {
        std::cout << player->getName() << " goes to jail\n";
        player->move_jail();
    } else if (action == 6) {
        std::cout << player->getName() << " moves to first train station\n";
        player->move(40 - player->getPosition());
    } else if (action == 7) {
        std::cout << player->getName() << " moves backward 5 spaces\n";
        player->move(31 - player->getPosition());
    } else if (action == 8) {
        std::cout << player->getName() << " moves to property number 20\n";
        if (player->getPosition() < 20)
            player->move(20 - player->getPosition());
        else
            player->move(56 - player->getPosition());
    } else if (action == 9) {
        std::cout << player->getName() << " gets nothing from this card\n";
    }
}

/**
 * @brief Displays a message specific to the Chance property.
 */
void Chance::Display() const {
    std::cout << name << " received the bonus from chance\n";
}

/**
 * @brief Creates a copy of the Chance object.
 *
 * @return A pointer to the newly created copy of the Chance object.
 */
Property *Chance::clone() const {
    return new Chance(*this);
}
