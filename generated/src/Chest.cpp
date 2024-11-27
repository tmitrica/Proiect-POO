#include "Chest.h"

Chest::Chest(const std::string& name, int price, int rent) {
    this->name = name;
    this->price = price;
    this->rent = rent;
}

void Chest::ApplyEffect(Player *player) const {
    int action = rand() % 10;///generating a random action
    if (action == 0) {
        std::cout << player->getName() << " pays 500 for taxes\n";
        player->buy(500);
    } else if (action == 1) {
        std::cout << player->getName() << " receives 150 for income\n";
        player->buy(-150);
    } else if (action == 2) {
        std::cout << player->getName() << " receives 300 from an uncle\n";
        player->buy(-300);
    } else if (action == 3) {
        std::cout << player->getName() << " pays 300 for ANAF\n";
        player->buy(300);
    } else if (action == 4) {
        std::cout << player->getName() << " pays 800 for fines\n";
        player->buy(800);
    } else if (action == 5) {
        std::cout << player->getName() << " found 10 on the street\n";
        player->buy(-10);
    } else if (action == 6) {
        std::cout << player->getName() << " pays 123 to DDD\n";
        player->buy(123);
    } else if (action == 7) {
        std::cout << player->getName() << " receives 137 from a cousin\n";
        player->buy(-137);
    } else if (action == 8) {
        std::cout << player->getName() << " dropped 1 from their pocket\n";
        player->buy(1);
    } else if (action == 9)
        std::cout << player->getName() << " gets nothing from this card \n";
}
