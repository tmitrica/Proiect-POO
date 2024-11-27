#ifndef CHEST_H
#define CHEST_H

#include "Property.h"

class Chest : public Property {
public:
    Chest(const std::string& name, int price, int rent);

    void ApplyEffect(Player *player) const override;
};


#endif //CHEST_H
