#include "Board.h"
#include "Exception.h"

int Board::properties_count = 0;

Board::Board(const std::string &f) {
    properties.reserve(36);
    /// we will create a board consisting of 36 properties, which we will read from the file

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
            //start jail
            if (i != 0 && i != 9) {
                throw SpecialPropertyPlacementException(i, name);
            }
            properties.push_back(new Property(name, price, rent, 2));
        } else if (price == 5) {
            //stations
            if (i != 4 && i != 12 && i != 24 && i != 32) {
                throw SpecialPropertyPlacementException(i, name);
            }
            properties.push_back(new Property(name, price, rent, 2));
        } else if (price == 6) {
            //go_to_jail
            if (i != 27) {
                throw SpecialPropertyPlacementException(i, name);
            }
            properties.push_back(new Property(name, price, rent, 2));
        } else {
            properties.push_back(new Property(name, price, rent));
        }

        properties_count++;
    }

    file.close();

    if (properties_count != 36) {
        throw BaseException("Incorrect number of properties on the board.");
    }
}

int Board::getProperties_count() {
    return properties_count;
}

Property &Board::getProperty(const int position) const {
    return *properties[position];
} /// retrieves the current property on which a player has landed

Board::~Board() {
    for (const auto &property: properties) {
        properties_count--;
        delete property;
    }
}
