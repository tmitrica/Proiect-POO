#ifndef PROPERTYFACTORY_H
#define PROPERTYFACTORY_H

#include <string>
#include "Property.h"
#include "Chest.h"
#include "Chance.h"
#include "Parking.h"
#include "Exception.h"

/**
 * @class PropertyFactory
 * @brief Factory class for creating Property objects.
 *
 * This class provides static methods to create normal or special properties on the game board.
 * It ensures proper placement of special properties based on board rules.
 */
class PropertyFactory {
public:
    /**
     * @brief Creates a normal property.
     *
     * This method creates a regular `Property` object without requiring a specific position.
     *
     * @param name The name of the property.
     * @param price The price of the property.
     * @param rent The rent value of the property.
     * @return A pointer to the created `Property` object.
     */
    static Property* createProperty(const std::string& name, int price, int rent);

    /**
     * @brief Creates a special property.
     *
     * This method creates a `Chest`, `Chance`, `Parking`, or other special property, ensuring
     * proper placement based on the given position.
     *
     * @param name The name of the property.
     * @param price The price of the property.
     * @param rent The rent value of the property.
     * @param position The position of the property on the board.
     * @return A pointer to the created `Property` object.
     * @throws SpecialPropertyPlacementException If the property is placed in an invalid position.
     */
    static Property* createSpecialProperty(const std::string& name, int price, int rent, int position);
};

#endif // PROPERTYFACTORY_H
