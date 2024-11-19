#include "Board.h"

Board::Board(const std::string &f) {
    properties = new Property[36];
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
        properties[i] = Property(name, price, rent);
    }
    file.close();
}

const Property &Board::getProperty(const int position) const {
    return properties[position];
} /// retrieves the current property on which a player has landed

Board::~Board() {
    delete[] properties; /// destructor
}
