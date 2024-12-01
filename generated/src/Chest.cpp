#include "Chest.h"

/**
 * @file Chest.cpp
 * @brief Implementation of the Chest class, a derived class from Property, which applies random financial effects to players.
 */

/**
 * @brief Constructs a Chest object with the specified name, price, and rent.
 *
 * @param name The name of the Chest property.
 * @param price The price of the property.
 * @param rent The rent of the property (not used in Chest effects).
 */
Chest::Chest(const std::string &name, const int price, const int rent) : Property(name, price, rent) {
    this->name = name;
    this->price = price;
    this->rent = rent;
}

/**
 * @brief Applies a random financial effect to the specified player.
 *
 * @details The effect is chosen randomly from 10 possible outcomes:
 * - **0:** Player pays 500 for taxes.
 * - **1:** Player receives 150 from income.
 * - **2:** Player receives 300 from a relative.
 * - **3:** Player pays 300 to ANAF.
 * - **4:** Player pays 800 for fines.
 * - **5:** Player finds 10 on the street.
 * - **6:** Player pays 123 to DDD.
 * - **7:** Player receives 137 from a cousin.
 * - **8:** Player loses 1 dollar (drops it from their pocket).
 * - **9:** No effect ("nothing happens").
 *
 * @param player A pointer to the Player object affected by the Chest card.
 */
void Chest::ApplyEffect(Player *player) const {
    int action = rand() % 10; ///< Randomly generating an action.

    if (action == 0) {
        std::cout << player->getName() << " pays 500 for taxes\n";
        player->buy(500);
    } else if (action == 1) {
        std::cout << player->getName() << " receives 150 for income\n";
        player->buy(-150);
    } else if (action == 2) {
        std::cout << player->getName() << " receives 300 from an uncle\n";
        player->buy(-300);
    } else if (action == 3) {
        std::cout << player->getName() << " pays 300 for ANAF\n";
        player->buy(300);
    } else if (action == 4) {
        std::cout << player->getName() << " pays 800 for fines\n";
        player->buy(800);
    } else if (action == 5) {
        std::cout << player->getName() << " found 10 on the street\n";
        player->buy(-10);
    } else if (action == 6) {
        std::cout << player->getName() << " pays 123 to DDD\n";
        player->buy(123);
    } else if (action == 7) {
        std::cout << player->getName() << " receives 137 from a cousin\n";
        player->buy(-137);
    } else if (action == 8) {
        std::cout << player->getName() << " dropped 1 from their pocket\n";
        player->buy(1);
    } else if (action == 9) {
        std::cout << player->getName() << " gets nothing from this card\n";
    }
}

/**
 * @brief Displays the Chest property details.
 *
 * @details Outputs the name and price of the Chest property.
 */
void Chest::Display() const {
    std::cout << "Chest: " << name << ", Bonus: " << price << "\n";
}

/**
 * @brief Creates a copy of the Chest object.
 *
 * @return A pointer to the newly created copy of the Chest object.
 */
Property *Chest::clone() const {
    return new Chest(*this);
}
