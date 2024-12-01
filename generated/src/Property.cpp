#include "Property.h"

/**
 * @file Property.cpp
 * @brief Implementation of the abstract Property class, representing properties on the game board.
 */

/**
 * @brief Constructs a Property object with the specified attributes.
 *
 * @param name The name of the property.
 * @param price The price of the property.
 * @param rent The rent of the property.
 * @param owned The ownership status of the property (0 for unowned, 1 for owned).
 * @param owner A pointer to the owner of the property, or nullptr if unowned.
 */
Property::Property(const std::string &name, const int price, const int rent, const int owned, Player *const owner) {
    this->name = name;
    this->price = price;
    this->rent = rent;
    this->owned = owned;
    this->owner = owner;
}

/**
 * @brief Handles the purchase of the property by a player.
 *
 * @details Determines whether the property is a special space, unowned, or owned, and updates its ownership status accordingly.
 *
 * @param player A pointer to the Player attempting to buy the property.
 * @return An integer code:
 * - `3` for community chest.
 * - `4` for chance.
 * - `5` for train station.
 * - `2` for visiting jail or start.
 * - `8` for paid parking.
 * - `6` for go to jail.
 * - `1` if the property was successfully purchased.
 * - `7` if the player doesn't have enough balance to buy it.
 * - `0` if the property is already owned.
 */
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
}

/**
 * @brief Retrieves the name of the property.
 *
 * @return A reference to the property's name.
 */
const std::string &Property::getName() const {
    return name;
}

/**
 * @brief Retrieves the owner of the property.
 *
 * @return A pointer to the Player object who owns the property, or nullptr if unowned.
 */
Player *Property::getOwner() const {
    return owner;
}

/**
 * @brief Sets the ownership status of the property.
 *
 * @param local_owned The new ownership status (0 for unowned, 1 for owned).
 */
void Property::setOwned(const int local_owned) {
    this->owned = local_owned;
}

/**
 * @brief Applies the effect of the property on the specified player.
 *
 * @details This is intended to be overridden by derived classes for specific property behavior.
 *
 * @param player A pointer to the Player object affected by the property.
 */
void Property::ApplyEffect(Player *player) const {
    std::cout << player->getName() << std::endl;
}

/**
 * @brief Displays information about the property.
 *
 * @details This is a placeholder function necessary for the virtual table (vtable) in abstract classes.
 */
void Property::Display() const {
    std::cout << "This is a generic property. Should not be directly used.\n";
}

/**
 * @brief Clones the Property object.
 *
 * @details Throws an exception because cloning an abstract Property object is not allowed.
 *
 * @return A pointer to the cloned Property object.
 * @throws std::runtime_error if attempting to clone an abstract object.
 */
Property *Property::clone() const {
    throw std::runtime_error("Cannot clone an abstract Property object.");
}

/**
 * @brief Retrieves the ownership status of the property.
 *
 * @return An integer representing ownership (0 for unowned, 1 for owned).
 */
int Property::getOwned() const {
    return owned;
}

/**
 * @brief Sets the owner of the property.
 *
 * @param local_owner A pointer to the Player object who will own the property, or nullptr if unowned.
 */
void Property::setOwner(Player *local_owner) {
    this->owner = local_owner;
}

/**
 * @brief Retrieves the rent value of the property.
 *
 * @return The rent value as an integer.
 */
int Property::getRent() const {
    return rent;
}
