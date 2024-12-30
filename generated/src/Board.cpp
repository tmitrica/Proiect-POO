/**
 * @file Board.cpp
 * @brief Implementation of the Board class, representing the game board.
 *
 * This file implements the methods for managing properties on the board. It reads property data from a file,
 * creates properties using the `PropertyFactory`, and provides access to the properties by position.
 *
 * @see Board
 * @see PropertyFactory
 */
#include "Board.h"
#include "PropertyFactory.h"
#include "Exception.h"

int Board::properties_count = 0;

/**
 * @brief Constructs the board by reading property data from a file.
 *
 * This constructor reads property data from a file and uses the `PropertyFactory` to create the properties.
 * It ensures that special properties are placed in the correct positions, throwing exceptions if any errors
 * occur during the creation of properties.
 *
 * @param f The filename containing property data.
 * @throws FileNotFoundException If the file cannot be opened.
 * @throws SpecialPropertyPlacementException If a special property is placed incorrectly.
 * @throws BaseException If the number of properties is not equal to 36.
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

        // Use PropertyFactory to create the property
        try {
            properties.push_back(PropertyFactory::createProperty(name, price, rent, i));
        } catch (const SpecialPropertyPlacementException& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            continue;  // Continue processing other properties even if one is invalid
        }

        properties_count++;
    }

    file.close();

    if (properties_count != 36) {
        throw BaseException("Incorrect number of properties on the board.");
    }
}

/**
 * @brief Returns the total number of properties on the board.
 *
 * @return The number of properties on the board (36).
 */
int Board::getProperties_count() {
    return properties_count;
}

/**
 * @brief Retrieves a reference to the property at the specified position.
 *
 * This method returns a reference to the `Property` object at the given position on the board.
 *
 * @param position The position of the property (0-35).
 * @return A reference to the `Property` at the given position.
 */
Property &Board::getProperty(const int position) const {
    return *properties[position];
}

/**
 * @brief Destructor for the Board class.
 *
 * This destructor deletes all dynamically allocated properties from memory.
 */
Board::~Board() {
    for (auto &property : properties) {
        properties_count--;
        delete property;
    }
}
