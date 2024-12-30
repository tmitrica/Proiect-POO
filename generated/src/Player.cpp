#include "Player.h"

/**
 * @file Player.cpp
 * @brief Implementation of the Player class representing players in the Monopoly game.
 */

/**
 * @brief Constructs a Player object with the specified attributes.
 *
 * @param name The name of the player.
 * @param money The initial money of the player.
 * @param position The starting position of the player on the board.
 * @param jail The initial jail status of the player (0 if not in jail).
 * @param in_game The status of the player in the game (1 if active, 0 if eliminated).
 */
Player::Player(const std::string &name, const int money, const int position, const int jail, const int in_game) {
    this->name = name;
    this->money = money;
    this->position = position;
    this->jail = jail;
    this->in_game = in_game;
}

/**
 * @brief Moves the player forward by a specified number of positions on the board.
 *
 * @details If the player passes or lands on START, they collect $200, but their money is capped at $3000.
 *
 * @param pos The number of positions to move forward.
 */
void Player::move(const int pos) {
    if (position + pos >= 36) {
        money = std::min(money + 200, 3000);
    }

    position = (position + pos) % 36;
}

/**
 * @brief Moves the player to the next train station on the board.
 *
 * @details If the player passes START while moving, they collect $200, capped at $3000.
 *
 * @return The new position of the player.
 */
void Player::move_train() {
    if (position == 4) {
        position = 12;
        std::cout << name << " new position: " << position << '\n';
    } else if (position == 12) {
        position = 24;
        std::cout << name << " new position: " << position << '\n';
    } else if (position == 24) {
        position = 32;
        std::cout << name << " new position: " << position << '\n';
    }
    else if (position == 32) {
        position = 4;
        money = std::min(money + 200, 3000);
        std::cout<< name << " new position: " << position << '\n';
    }
}


/**
 * @brief Moves the player to jail and manages their jail status.
 *
 * @details The player must stay in jail for up to 2 turns. On the third turn, they can roll the dice again.
 */
void Player::move_jail() {
    if (jail < 2) {
        position = 9;
        jail++;
        std::cout << name << " still in jail" << "\n";
    } else if (jail == 2) {
        jail = 0;
    }
}

/**
 * @brief Deducts the specified amount from the player's balance to purchase a property.
 *
 * @param price The price of the property.
 * @return An integer indicating the result:
 * - `1` if the purchase is successful.
 * - `0` if the player does not have enough money.
 */
int Player::buy(const int price) {
    if (money >= price) {
        money -= price;
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Retrieves the player's current position on the board.
 *
 * @return The player's current position.
 */
int Player::getPosition() const {
    return position;
}

/**
 * @brief Retrieves the player's current balance.
 *
 * @return The player's current money.
 */
int Player::getMoney() const {
    return money;
}

/**
 * @brief Retrieves the player's name.
 *
 * @return A constant reference to the player's name.
 */
const std::string &Player::getName() const {
    return name;
}

/**
 * @brief Retrieves the player's jail status.
 *
 * @return The number of turns the player has been in jail.
 */
int Player::getJail() const {
    return jail;
}

/**
 * @brief Adds a specified amount of rent money to the player's balance.
 *
 * @details The player's balance is capped at $3000.
 *
 * @param local_money The amount of money to add.
 */
void Player::ReceiveRent(const int local_money) {
    money = std::min(money + local_money, 3000);
}

/**
 * @brief Deducts a specified amount of rent money from the player's balance.
 *
 * @param local_money The amount of money to deduct.
 */
void Player::PayRent(const int local_money) {
    money -= local_money;
}

/**
 * @brief Retrieves the player's game status.
 *
 * @return `1` if the player is still in the game, `0` if they are eliminated.
 */
int Player::getIn_Game() const {
    return in_game;
}

/**
 * @brief Sets the player's game status.
 *
 * @param local_in_game The new game status (`1` for active, `0` for eliminated).
 */
void Player::setIn_Game(const int local_in_game) {
    in_game = local_in_game;
}

/**
 * @brief Adds an observer to the player's list of observers.
 *
 * @param observer The observer to be added.
 */
void Player::addObserver(Observer *observer) {
    observers.push_back(observer);
}
