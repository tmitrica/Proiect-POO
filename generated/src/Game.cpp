#include "Game.h"

Game::Game(const std::string &f, const std::string &g): board(g) {
    std::ifstream file(f);
    if (!file.is_open()) {
        std::cout << "file error" << f << '\n';
        exit(2);
    }

    std::string name;
    file >> players_number;
    players = new Player[players_number];

    for (int i = 0; i < players_number; ++i) {
        file >> name;
        players[i] = Player(name);
    }
    file.close();
} /// constructor to initialize the board and read players from the file, as well as their count

void Game::Turn(const int currentPlayer) const {
    Player &player = players[currentPlayer];

    if (player.getJail() == 0) {
        const int dice1 = rand() % 6 + 1;
        const int dice2 = rand() % 6 + 1;
        const int dice = dice1 + dice2;
        player.move(dice);

        auto &property = const_cast<Property &>(board.getProperty(player.getPosition()));

        int landed = property.buy(&player);
        if (landed == 1)
            std::cout << player.getName() << " at position " << player.getPosition() << " bought property " << property.
                    getName() << '\n';
        else if (landed == 3)
            std::cout << player.getName() << " at position " << player.getPosition() <<
                    " landed on a community chest\n";
        else if (landed == 4)
            std::cout << player.getName() << " at position " << player.getPosition() << " landed on a chance\n";
        else if (landed == 5)
            std::cout << player.getName() << " at position " << player.getPosition() <<
                    " landed on a train station and got moved to "
                    << player.move_train() << '\n';
        else if (landed == 2)
            std::cout << player.getName() << " at position " << player.getPosition() << " landed on a neutral space\n";
        else if (landed == 6) {
            std::cout << player.getName() << " must go to jail for 3 rounds\n";
            player.move_jail();
        } else
            std::cout << player.getName() << " at position " << player.getPosition() <<
                    " property owned or insufficient funds\n";
    } else player.move_jail();
}

/// this function simulates a player's turn in the game; first, we check if the current player is in jail
/// if they are in jail, we update the remaining number of turns until they can play again
/// if not, we roll the dice using the random function, then move the player accordingly; we check the tile the player landed on
/// apply the tile's effects on the player and display what happened at the end of the turn

Game::~Game() {
    delete[] players;
} /// destructor
