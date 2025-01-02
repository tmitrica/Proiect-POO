#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Property.h"

/**
 * @class Board
 * @brief Represents the game board containing properties.
 *
 * This class manages a collection of properties on the board, reading their data from a file
 * and providing access to them based on their position.
 */
class Board {
private:
    std::vector<Property*> properties; ///< List of properties on the board.
    static int properties_count;       ///< Count of the properties on the board.

public:
    /**
     * @brief Constructs the board by reading property data from a file.
     *
     * @param f The filename containing property data.
     * @throws FileNotFoundException If the file cannot be opened.
     * @throws SpecialPropertyPlacementException If a special property is placed incorrectly.
     * @throws BaseException If the number of properties is not equal to 36.
     */
    explicit Board(const std::string &f);

    /**
     * @brief Returns the total number of properties on the board.
     *
     * @return The number of properties on the board (36).
     */
    static int getProperties_count();

    /**
     * @brief Retrieves a reference to the property at the specified position.
     *
     * @param position The position of the property (0-35).
     * @return A reference to the `Property` at the given position.
     */
    Property &getProperty(int position) const;

    /**
     * @brief Destructor for the Board class.
     *
     * This destructor deletes all dynamically allocated properties from memory.
     */
    ~Board();
};

#endif // BOARD_H
