#include "Game.h"

#include <Chance.h>
#include <Chest.h>
#include <Parking.h>

#include "Exception.h"

/**
 * @file Game.cpp
 * @brief Implementation of the Game class, which manages the core gameplay logic.
 */

/**
 * @brief Constructs a Game object by initializing the board and loading players from a file.
 *
 * @param f The filename containing player information.
 * @param g The filename containing board information.
 * @throws FileNotFoundException If the file containing player data cannot be opened.
 * @throws PlayerException If a player's attributes are invalid after initialization.
 */
Game::Game(const std::string &f, const std::string &g) : board(g) {
    std::ifstream file(f);
    if (!file.is_open()) {
        throw FileNotFoundException("Failed to open file: " + f);
    }

    std::string name;
    file >> players_number;
    players = new Player[players_number];

    for (int i = 0; i < players_number; i++) {
        file >> name;
        players[i] = Player(name);

        if (players[i].getName() != name && players[i].getMoney() != 750 && players[i].getPosition() != 0
            && players[i].getJail() != 0) {
            throw PlayerException(players[i].getName());
        }

        players[i].addObserver(&logger);
    }

    file.close();
}

/**
 * @brief Simulates a player's turn in the game.
 *
 * @param currentPlayer The index of the current player in the array.
 * @param turn The current turn number.
 * @return An integer indicating the game's state:
 * - 0 if the game has ended.
 * - Recursive call to Turn to process the next player's turn.
 *
 * @details The function handles several scenarios:
 * - If the current player is inactive, it moves to the next active player.
 * - Ends the game when only one active player remains or after 250 turns.
 * - Rolls dice for the player and moves them on the board.
 * - Applies the effects of the tile they land on (property purchase, rent payment, community chest, etc.).
 */
int Game::Turn(const int currentPlayer, const int turn) {
    std::cout << "Turn: " << turn << '\n';

    // Check if currentPlayer is active
    if (players[currentPlayer].getIn_Game() == 0) {
        int nextPlayer = (currentPlayer + 1) % players_number;
        while (players[nextPlayer].getIn_Game() == 0 && nextPlayer != currentPlayer) {
            nextPlayer = (nextPlayer + 1) % players_number;
        }

        if (players[nextPlayer].getIn_Game() == 0) {
            std::cout << "No active players left. The game has ended.\n";
            return 0;
        }
        return Turn(nextPlayer, turn); // Continue with the next active player
    }

    // Check for remaining active players
    int activePlayers = 0;
    int lastActivePlayerIndex = -1;
    for (int i = 0; i < players_number; i++) {
        if (players[i].getIn_Game() == 1) {
            activePlayers++;
            lastActivePlayerIndex = i;
        }
    }

    // End the game if only one player remains
    if (activePlayers == 1) {
        std::cout << "Player " << players[lastActivePlayerIndex].getName() << " has won.\n";
        return 0;
    }

    // End the game after 250 turns
    if (turn == 250) {
        std::cout << "The game ended after 250 turns\n";

        int max = 0;
        std::string winner;
        for (int i = 0; i < players_number; i++) {
            if (players[i].getMoney() > max) {
                max = players[i].getMoney();
                winner = players[i].getName();
            }
        }
        std::cout << winner << " won by having the most amount of money " << max << '\n';
        return 0;
    }

    // Process each player's turn
    for (int i = 0; i < players_number; ++i) {
        if (players[i].getIn_Game() == 1) {
            Player &player = players[i];
            if (player.getJail() == 0) {
                const int dice1 = rand() % 6 + 1;
                const int dice2 = rand() % 6 + 1;
                const int dice = dice1 + dice2;
                player.move(dice);

                auto &property = const_cast<Property &>(board.getProperty(player.getPosition()));

                // Handle special property types
                if (dynamic_cast<Chest *>(&property)) {
                    processSpecialProperty<Chest>(property, player, logger, "community chest");
                } else if (dynamic_cast<Chance *>(&property)) {
                    processSpecialProperty<Chance>(property, player, logger, "chance");
                } else if (dynamic_cast<Parking *>(&property)) {
                    processSpecialProperty<Parking>(property, player, logger, "paid parking");
                } else {
                    // Handle property purchase or rent payment
                    int landed = property.buy(&player);
                    if (landed == 1)
                        logger.update(player.getName() + " at position " + std::to_string(player.getPosition()) + " bought property " + property.getName());
                    else if (landed == 5) {
                        logger.update(player.getName() + " at position " + std::to_string(player.getPosition()) + " landed on a train station");
                        player.move_train();
                    }
                    else if (landed == 2)
                        logger.update(player.getName() + " at position " + std::to_string(player.getPosition()) + " landed on a neutral space");
                    else if (landed == 6) {
                        logger.update(player.getName() + " must go to jail for 3 rounds");
                        player.move_jail();
                    } else if (landed == 7)
                        logger.update(player.getName() + " at position " + std::to_string(player.getPosition()) + " insufficient funds for this property");
                    else {
                        Player *owner = property.getOwner();
                        const int rent = property.getRent();

                        if (owner == &player) {
                            logger.update(player.getName() + " at position " + std::to_string(player.getPosition()) + " owns this property");
                        } else if (player.getMoney() >= rent && player.getName() != owner->getName()) {
                            logger.update(player.getName() + " at position " + std::to_string(player.getPosition()) + " paid rent " + std::to_string(rent) + " to " + owner->getName());
                            owner->ReceiveRent(rent);
                            player.PayRent(rent);
                        } else if (player.getMoney() < rent && player.getName() != owner->getName()) {
                            logger.update(player.getName() + " at position " + std::to_string(player.getPosition()) + " can't pay rent " + std::to_string(rent) + " to " + owner->getName());

                            // Handle player bankruptcy
                            for (int j = 0; j < 36; j++) {
                                auto &property1 = const_cast<Property &>(board.getProperty(j));
                                if (property1.getOwned() == 1 && property1.getOwner()->getName() == players[i].getName()) {
                                    property1.setOwned(0);
                                    property1.setOwner(nullptr);
                                }
                            }

                            logger.update(players[i].getName() + " has lost");
                            players[i].setIn_Game(0);
                        }
                    }
                }
            } else {
                player.move_jail();
            }
        }
    }

    // Check for next active player
    int nextPlayer = (currentPlayer + 1) % players_number;
    while (players[nextPlayer].getIn_Game() == 0 && nextPlayer != currentPlayer) {
        nextPlayer = (nextPlayer + 1) % players_number;
    }

    if (players[nextPlayer].getIn_Game() == 0) {
        std::cout << "No active players left. The game has ended.\n";
        return 0;
    }

    return Turn(nextPlayer, turn + 1);
}


/**
 * @brief Destructor for the Game class. Cleans up dynamically allocated player data.
 */
Game::~Game() {
    delete[] players;
}