#ifndef CHANCE_H
#define CHANCE_H

#include "Property.h"

class Chance : public Property {
public:
    Chance(const std::string& name, int price, int rent);

    void ApplyEffect(Player *player) const override;
};



#endif //CHANCE_H
