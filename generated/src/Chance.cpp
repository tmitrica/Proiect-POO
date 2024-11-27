#include "Chance.h"

Chance::Chance(const std::string& name, int price) {
    this->name = name;
    this->price = price;
}

void Chance::ApplyEffect(Player *player) const {

        int action = rand() % 10;///generating a random action
        if (action == 0) {
            std::cout << player->getName() << " pays 500 for taxes\n";
            player->buy(500);
        } else if (action == 1) {
            std::cout << player->getName() << " receives 150 for income\n";
            player->buy(-150);
        } else if (action == 2) {
            std::cout << player->getName() << " moves to START\n";
            player->move(36 - player->getPosition());
        } else if (action == 3) {
            std::cout << player->getName() << " moves forward 3 spaces\n";
            player->move(3);
        } else if (action == 4) {
            std::cout << player->getName() << " moves backward 3 spaces\n";
            player->move(33);
        } else if (action == 5) {
            std::cout << player->getName() << "goes to jail\n";
            player->move_jail();
        } else if (action == 6) {
            std::cout << player->getName() << " moves to first train station\n";
            player->move(40 - player->getPosition());
        } else if (action == 7) {
            std::cout << player->getName() << " moves backward 5 spaces\n";
            player->move(31 - player->getPosition());
        } else if (action == 8) {
            std::cout << player->getName() << " moves to property  number 20\n";
            if(player->getPosition() < 20)
            player->move(20 - player->getPosition());
            else player->move(56 - player->getPosition());
        } else if (action == 9)
            std::cout << player->getName() << " gets nothing from this card \n";
}

