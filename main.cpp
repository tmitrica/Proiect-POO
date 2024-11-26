#include<fstream>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cassert>
#include "Game.h"

/*
This code simulates a simplified Monopoly game; I will make a few clarifications regarding the order of the tiles on the board and their effects.
The board will have 36 properties indexed from 0, 1, 2... to 35.

START is located at position 0, and every time a player passes or lands on it, they will receive $200.
Station will move the player to the next station; these are always located at positions 4, 12, 24, and 32.
Chance and Community Chest have not been implemented yet and can be considered neutral tiles (they have no effect on the player).
Parking and Jail (visiting) are neutral tiles.
go_to_jail will send the player to jail, which is always located at position 9; the player will wait 3 turns here before being able to play again.

The properties will be read from the file board.txt in the format: name price (integer >10) rent (integer).
The number of players and their details will be read from the file players.txt.

A player wins when he/she is the only one left with money or the game will end automatically after 250 turns and the winner is the player with the most amount of money
If more than one player have the same amount of winning money(at the end) the winner will be the first one read from the file.
 */

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); /// initialize seed for random

    /// test the game itself for the functionality of the Turn function and board initialization
    Game game("players.txt", "board.txt"); /// generate the game using the files
    std::cout << '\n';
    game.Turn(0, 1);

    return 0;
}
