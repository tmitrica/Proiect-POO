#include "Board.h"

Board::Board(const std::string &f) {
    properties = new Property*[36];
    /// we will create a board consisting of 36 properties, which we will read from the file

    std::ifstream file(f);
    if (!file.is_open()) {
        std::cout << "file error" << f << '\n';
        exit(1);
    }
    std::string name;
    int price, rent;

    for (int i = 0; i < 36; ++i) {
        file >> name >> price >> rent;
        if (price == 3)
            properties[i] = new Chest(name, price, rent);
        else if (price == 4)
            properties[i] = new Chance(name, price, rent);
        else if (price == 8)
            properties[i] = new Parking(name, price, rent);
        else if (price < 10)
            properties[i] = new Property(name, price, rent,2);
        else
            properties[i] = new Property(name, price, rent);
    }
    file.close();
}

Property &Board::getProperty(const int position) const {
    return *properties[position];
} /// retrieves the current property on which a player has landed

Board::~Board() {
    for (int i = 0; i < 36; ++i)
        delete properties[i];
    delete[] properties;
}
