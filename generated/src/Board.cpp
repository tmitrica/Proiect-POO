#include "Board.h"
#include "Exception.h"

/**
 * @file Board.cpp
 * @brief Implementation of the Board class, representing the game board.
 */

/**
 * @brief Static member initialization for the property count on the board.
 */
int Board::properties_count = 0;

/**
 * @brief Constructs the Board object by reading properties from a file.
 *
 * @param f The filename containing the board properties.
 * @throws FileNotFoundException If the file cannot be opened.
 * @throws SpecialPropertyPlacementException If special properties are incorrectly positioned.
 * @throws BaseException If the total number of properties is not equal to 36.
 *
 * @details The board consists of 36 properties read from the file. Each property is either:
 * - A regular property
 * - A special property (Chest, Chance, Parking, etc.)
 * The constructor enforces specific positions for special properties.
 */
Board::Board(const std::string &f) {
    properties.reserve(36);

    std::ifstream file(f);
    if (!file.is_open()) {
        throw FileNotFoundException("Failed to open file: " + f);
    }

    std::string name;
    int price, rent;

    for (int i = 0; i < 36; ++i) {
        file >> name >> price >> rent;

        if (price == 3) {
            // Chest
            if (i != 2 && i != 15 && i != 30) {
                throw SpecialPropertyPlacementException(i, name);
            }
            properties.push_back(new Chest(name, price, rent));
        } else if (price == 4) {
            // Chance
            if (i != 6 && i != 21 && i != 33) {
                throw SpecialPropertyPlacementException(i, name);
            }
            properties.push_back(new Chance(name, price, rent));
        } else if (price == 8) {
            // Parking
            if (i != 18) {
                throw SpecialPropertyPlacementException(i, name);
            }
            properties.push_back(new Parking(name, price, rent));
        } else if (price == 2) {
            // Start or Jail
            if (i != 0 && i != 9) {
                throw SpecialPropertyPlacementException(i, name);
            }
            properties.push_back(new Property(name, price, rent, 2));
        } else if (price == 5) {
            // Stations
            if (i != 4 && i != 12 && i != 24 && i != 32) {
                throw SpecialPropertyPlacementException(i, name);
            }
            properties.push_back(new Property(name, price, rent, 2));
        } else if (price == 6) {
            // Go to Jail
            if (i != 27) {
                throw SpecialPropertyPlacementException(i, name);
            }
            properties.push_back(new Property(name, price, rent, 2));
        } else {
            // Regular property
            properties.push_back(new Property(name, price, rent));
        }

        properties_count++;
    }

    file.close();

    if (properties_count != 36) {
        throw BaseException("Incorrect number of properties on the board.");
    }
}

/**
 * @brief Retrieves the total number of properties on the board.
 *
 * @return The number of properties on the board.
 */
int Board::getProperties_count() {
    return properties_count;
}

/**
 * @brief Retrieves a reference to the property at the specified position.
 *
 * @param position The position of the property on the board (0-35).
 * @return A reference to the `Property` object at the specified position.
 */
Property &Board::getProperty(const int position) const {
    return *properties[position];
}

/**
 * @brief Destructor for the Board class. Frees allocated memory for properties.
 *
 * @details Iterates through all properties, deletes each one, and decrements the property count.
 */
Board::~Board() {
    for (const auto &property: properties) {
        properties_count--;
        delete property;
    }
}
