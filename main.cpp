#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <Exception.h>
#include "Game.h"

/**
 * @file main.cpp
 * @brief Entry point for the Monopoly game simulation.
 *
 * This code simulates a simplified Monopoly game. The board consists of 36 properties, each with unique effects.
 * The game ends when there is only one player left with money or after 250 turns, at which point the winner is
 * determined based on the highest balance.
 *
 * @details
 * **Board Description:**
 * - START is located at position 0; players receive $200 when passing or landing on it.
 * - **Stations:** Move the player to the next station (positions 4, 12, 24, and 32).
 * - **Chance:** Applies an effect (positive or negative) to the player.
 * - **Chest:** Modifies the player's balance (positive or negative).
 * - **Jail (visiting):** Neutral tile.
 * - **Go to Jail:** Sends the player to Jail (position 9), where they skip 3 turns.
 *
 * **Input Files:**
 * - `board.txt`: Contains property details in the format `name price rent`.
 * - `players.txt`: Contains the number of players and their details.
 *
 * **Game Rules:**
 * - A player wins by being the last one with money or by having the highest balance after 250 turns.
 * - If multiple players have the same balance at the end, the winner is the first one read from the file.
 */

/**
 * @brief Entry point for the program.
 *
 * The main function initializes the game, handles exceptions, and simulates a turn.
 *
 * @return int Returns 0 on successful execution.
 */
int main() {
    srand(static_cast<unsigned int>(time(nullptr))); ///< Seed for random number generation.

    try {
        /**
         * @brief Create a Game instance using player and board data.
         *
         * @throws SpecialPropertyPlacementException If special properties are placed incorrectly on the board.
         * @throws FileNotFoundException If the required files are not found.
         * @throws PlayerException If player details are invalid.
         */
        Game game("players.txt", "board.txt"); ///< Initialize the game using the input files.
    } catch (const SpecialPropertyPlacementException &e) {
        std::cout << e.what() << '\n'; ///< Output error if special properties are misplaced.
    } catch (const FileNotFoundException &e) {
        std::cout << e.what() << '\n'; ///< Output error if the file is not found.
    } catch (const PlayerException &e) {
        std::cout << e.what() << '\n'; ///< Output error if player details are invalid.
    }

    /**
     * @brief Instantiate the game again for demonstration purposes.
     */
    Game game("players.txt", "board.txt");
    std::cout << '\n';

    /**
     * @brief Simulate a turn for player 0 in round 1.
     */
    game.Turn(0, 1);

    return 0;
}
