#ifndef PARKING_H
#define PARKING_H

#include "Property.h"


class Parking : public Property {
public:
    Parking(const std::string& name, int price, int rent);

    void ApplyEffect(Player *player) const override;
};


#endif //PARKING_H
