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

int Game::Turn(const int currentPlayer, const int turn) {
    std::cout << "Turn: " << turn << '\n';

    ///checking if currentPlayer is active
    if (players[currentPlayer].getIn_Game() == 0) {
        int nextPlayer = (currentPlayer + 1) % players_number;
        while (players[nextPlayer].getIn_Game() == 0 && nextPlayer != currentPlayer) {
            nextPlayer = (nextPlayer + 1) % players_number;
        }

        if (players[nextPlayer].getIn_Game() == 0) {
            std::cout << "No active players left. The game has ended.\n";
            return 0;
        }
        return Turn(nextPlayer, turn); ///we continue the turn with the next active player
    }

    int activePlayers = 0;
    int lastActivePlayerIndex = -1;
    for (int i = 0; i < players_number; i++) {
        if (players[i].getIn_Game() == 1) {
            activePlayers++;
            lastActivePlayerIndex = i;
        }
    }

    if (activePlayers == 1) {
        std::cout << "Player " << players[lastActivePlayerIndex].getName() << " has won.\n";
        return 0;
    } ///the game ends when there is only one active player

    if (turn == 250) {
        std::cout << "The game ended after 250 turns\n";

        int max = 0;
        std::string winner;
        for (int i = 0; i < players_number; i++) {
            if (players[i].getMoney() > max) {
                max = players[i].getMoney();
                winner = players[i].getName();
            }
        }
        std::cout << winner << " won by having the most amount of money " << max << '\n';
        return 0;
    } ///the game ends after 250 turns

    for (int i = 0; i < players_number; ++i) {
        if (players[i].getIn_Game() == 1) {
            Player &player = players[i];
            if (player.getJail() == 0) {
                const int dice1 = rand() % 6 + 1;
                const int dice2 = rand() % 6 + 1;
                const int dice = dice1 + dice2;
                player.move(dice);

                auto &property = const_cast<Property &>(board.getProperty(player.getPosition()));

                if (const auto *chest = dynamic_cast<Chest *>(&property)) {
                    std::cout << player.getName() << " at position " << player.getPosition() <<
                                " landed on a community chest\n";
                    chest->ApplyEffect(&player);
                } else if (const auto *chance = dynamic_cast<Chance *>(&property)) {
                    std::cout << player.getName() << " at position " << player.getPosition() <<
                                " landed on a chance\n";
                    chance->ApplyEffect(&player);
                } else if (const auto *parking = dynamic_cast<Parking *>(&property)) {
                    std::cout << player.getName() << " at position " << player.getPosition() <<
                                " landed on the paid parking\n";
                    parking->ApplyEffect(&player);
                } else {
                    int landed = property.buy(&player);
                    if (landed == 1)
                        std::cout << player.getName() << " at position " << player.getPosition() << " bought property "
                                <<
                                property.getName() << '\n';
                    else if (landed == 5)
                        std::cout << player.getName() << " at position " << player.getPosition() <<
                                " landed on a train station and got moved to " << player.move_train() << '\n';
                    else if (landed == 2)
                        std::cout << player.getName() << " at position " << player.getPosition() <<
                                " landed on a neutral space\n";
                    else if (landed == 6) {
                        std::cout << player.getName() << " must go to jail for 3 rounds\n";
                        player.move_jail();
                    } else if (landed == 7)
                        std::cout << player.getName() << " at position " << player.getPosition() <<
                                " insufficient funds for this property\n";
                    else {
                        Player *owner = property.getOwner();

                        const int rent = property.getRent();

                        if (owner == &player) {
                            std::cout << player.getName() << " at position " << player.getPosition() <<
                                    " owns this property\n";
                        } else if (player.getMoney() >= rent && player.getName() != owner->getName()) {
                            std::cout << player.getName() << " at position " << player.getPosition() << " paid rent " <<
                                    rent << " to " << owner->getName() << '\n';
                            owner->ReceiveRent(rent);
                            player.PayRent(rent);
                        } else if (player.getMoney() < rent && player.getName() != owner->getName()) {
                            std::cout << player.getName() << " at position " << player.getPosition() <<
                                    " can't pay rent "
                                    << rent << " to " << owner->getName() << '\n';

                            for (int j = 0; j < 36; j++) {
                                auto &property1 = const_cast<Property &>(board.getProperty(j));
                                if (property1.getOwned() == 1 && property1.getOwner()->getName() == players[i].
                                    getName()) {
                                    property1.setOwned(0);
                                    property1.setOwner(nullptr);
                                }
                            }

                            std::cout << players[i].getName() << " has lost\n";
                            players[i].setIn_Game(0);
                        }
                    }
                }
            } else {
                player.move_jail();
            }
        }
    }

    ///checking for next active player
    int nextPlayer = (currentPlayer + 1) % players_number;
    while (players[nextPlayer].getIn_Game() == 0 && nextPlayer != currentPlayer) {
        nextPlayer = (nextPlayer + 1) % players_number;
    }

    if (players[nextPlayer].getIn_Game() == 0) {
        std::cout << "No active players left. The game has ended.\n";
        return 0;
    }

    return Turn(nextPlayer, turn + 1);
}

/// this function simulates a player's turn in the game; first, we check if the current player is in jail
/// if they are in jail, we update the remaining number of turns until they can play again
/// if not, we roll the dice using the random function, then move the player accordingly; we check the tile the player landed on
/// apply the tile's effects on the player and display what happened at the end of the turn

Game::~Game() {
    delete[] players;
} /// destructor
