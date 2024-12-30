#ifndef PROPERTYFACTORY_H
#define PROPERTYFACTORY_H

/**
 * @file PropertyFactory.h
 * @brief A factory class for creating various types of properties on the board.
 *
 * This class is responsible for creating `Property`, `Chest`, `Chance`, `Parking`, and other special properties
 * based on the input data provided. It handles placement rules and throws exceptions if properties are placed
 * incorrectly.
 *
 * @see Property
 * @see Chest
 * @see Chance
 * @see Parking
 */

#include "Property.h"
#include "Chest.h"
#include "Chance.h"
#include "Parking.h"
#include "Exception.h"

/**
 * @class PropertyFactory
 * @brief Factory class responsible for creating properties.
 *
 * This class provides a static method `createProperty` to create instances of various types of `Property`
 * based on the price and position. It ensures that special properties are placed correctly according to their
 * rules and throws exceptions if they are not.
 */
class PropertyFactory {
public:
    /**
     * @brief Creates a property based on the provided price, rent, and position.
     *
     * This method creates a `Property`, `Chest`, `Chance`, `Parking`, or other special properties based on the
     * price and position values. It ensures that special properties are placed correctly on the board.
     *
     * @param name The name of the property.
     * @param price The price of the property.
     * @param rent The rent value of the property.
     * @param position The position of the property on the board.
     * @return A pointer to the created `Property` object.
     * @throws SpecialPropertyPlacementException If a special property is incorrectly placed.
     */
    static Property* createProperty(const std::string& name, int price, int rent, int position);
};

#endif //PROPERTYFACTORY_H
