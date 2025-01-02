#include "PropertyFactory.h"

/**
 * @brief Creates a normal property.
 *
 * This method creates a standard `Property` object without needing to validate its position.
 */
Property* PropertyFactory::createProperty(const std::string& name, const int price, const int rent) {
    return new Property(name, price, rent);
}

/**
 * @brief Creates a special property.
 *
 * This method ensures that special properties such as `Chest`, `Chance`, and `Parking` are placed
 * in the correct positions. If the placement is invalid, it throws an exception.
 */
Property* PropertyFactory::createSpecialProperty(const std::string& name, const int price, const int rent, const int position) {
    if (price == 3) {
        if (position == 2 || position == 15 || position == 30) {
            return new Chest(name, price, rent);
        } else {
            throw SpecialPropertyPlacementException(position, name);
        }
    } else if (price == 4) {
        if (position == 6 || position == 21 || position == 33) {
            return new Chance(name, price, rent);
        } else {
            throw SpecialPropertyPlacementException(position, name);
        }
    } else if (price == 8) {
        if (position == 18) {
            return new Parking(name, price, rent);
        } else {
            throw SpecialPropertyPlacementException(position, name);
        }
    } else if (price == 2) {
        if (position == 0 || position == 9) {
            return new Property(name, price, rent, 2);
        } else {
            throw SpecialPropertyPlacementException(position, name);
        }
    } else if (price == 5) {
        if (position == 4 || position == 12 || position == 24 || position == 32) {
            return new Property(name, price, rent, 2);
        } else {
            throw SpecialPropertyPlacementException(position, name);
        }
    } else if (price == 6) {
        if (position == 27) {
            return new Property(name, price, rent, 2);
        } else {
            throw SpecialPropertyPlacementException(position, name);
        }
    } else {
        throw BaseException("Invalid special property type.");
    }
}
