#ifndef PARKING_H
#define PARKING_H

#include "Property.h"


class Parking : public Property {
public:
    Parking(const std::string& name, int price, int rent);

    void ApplyEffect(Player *player) const override;

    // Funcție pentru afișare
    void Display() const override {
        std::cout << "Parking Space: " << name << " (Fee: 300)\n";
    }

    // Constructor virtual (clone)
    Parking* clone() const override {
        return new Parking(*this);  // Creează o copie a obiectului curent
    }

    // Copy constructor
    Parking(const Parking &other) : Property(other.name, other.price, other.rent) {}

    // Assignment operator (copy-and-swap idiom)
    Parking& operator=(Parking other) {
        swap(*this, other);
        return *this;
    }

    // Swap helper function
    friend void swap(Parking &first, Parking &second) {
        using std::swap;
        swap(first.name, second.name);
        swap(first.price, second.price);
        swap(first.rent, second.rent);
    }
};

#endif //PARKING_H
