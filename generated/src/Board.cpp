#include "Board.h"
#include "PropertyFactory.h"
#include "Exception.h"

/**
 * @brief Constructs the board by reading property data from a file.
 *
 * This constructor reads data from a file and creates properties using `PropertyFactory`.
 * Special properties are validated and placed in specific positions.
 *
 * @param f The filename containing property data.
 * @throws FileNotFoundException If the file cannot be opened.
 * @throws SpecialPropertyPlacementException If a special property is placed incorrectly.
 * @throws BaseException If the total number of properties is incorrect.
 */
int Board::properties_count = 0;
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

        try {
            if (price == 3 || price == 4 || price == 8 || price == 2 || price == 5 || price == 6) {
                properties.push_back(PropertyFactory::createSpecialProperty(name, price, rent, i));
            } else {
                properties.push_back(PropertyFactory::createProperty(name, price, rent));
            }
        } catch (const SpecialPropertyPlacementException& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            continue;
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
 * @brief Retrieves a reference to the property at a specified position.
 *
 * @param position The position of the property.
 * @return A reference to the `Property` object.
 */
Property& Board::getProperty(const int position) const {
    return *properties[position];
}

/**
 * @brief Destructor for the Board class.
 *
 * Frees memory allocated for all properties on the board.
 */
Board::~Board() {
    for (const auto& property : properties) {
        properties_count--;
        delete property;
    }
}
