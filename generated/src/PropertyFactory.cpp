#include "PropertyFactory.h"

// Static method to create properties based on price or type
Property* PropertyFactory::createProperty(const std::string& name, int price, int rent, int position) {
    if (price == 3) {
        // Chest
        if (position == 2 || position == 15 || position == 30) {
            return new Chest(name, price, rent);
        } else {
            throw SpecialPropertyPlacementException(position, name);
        }
    } else if (price == 4) {
        // Chance
        if (position == 6 || position == 21 || position == 33) {
            return new Chance(name, price, rent);
        } else {
            throw SpecialPropertyPlacementException(position, name);
        }
    } else if (price == 8) {
        // Parking
        if (position == 18) {
            return new Parking(name, price, rent);
        } else {
            throw SpecialPropertyPlacementException(position, name);
        }
    } else if (price == 2) {
        // Start or Jail
        if (position == 0 || position == 9) {
            return new Property(name, price, rent, 2); // Special handling for these positions
        } else {
            throw SpecialPropertyPlacementException(position, name);
        }
    } else if (price == 5) {
        // Stations
        if (position == 4 || position == 12 || position == 24 || position == 32) {
            return new Property(name, price, rent, 2); // Special handling for these positions
        } else {
            throw SpecialPropertyPlacementException(position, name);
        }
    } else if (price == 6) {
        // Go to Jail
        if (position == 27) {
            return new Property(name, price, rent, 2);
        } else {
            throw SpecialPropertyPlacementException(position, name);
        }
    } else {
        // Regular property
        return new Property(name, price, rent);
    }
}

