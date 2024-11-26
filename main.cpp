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

void testPlayer() {
    Player player("Teodor");
    player.move(15);
    assert(player.getPosition() == 15);

    player.move(30);
    assert(player.getPosition() == 9); /// will pass over 36 board tiles, so 45 % 36 = 9
    std::cout << "movement passed\n";

    const int result1 = player.buy(500);
    assert(result1 == 1); /// there will be sufficient funds

    const int result2 = player.buy(1200);
    assert(result2 == 1); /// there will be sufficient funds with the $200 collected at START

    const int result3 = player.buy(100);
    assert(result3 == 0); /// insufficient funds

    std::cout << "buying passed\n";
} /// tests the functions for moving on the board, collecting $200 at START, and buying properties

void testOwnership() {
    Player player("Teodor", 1500);
    Property property("Rahova", 500, 50);

    const int result1 = property.buy(&player);
    assert(result1 == 1); /// the property can be purchased

    const int result2 = property.buy(&player);
    assert(result2 == 0); /// cannot be purchased again (it is already owned)

    std::cout << "ownership passed\n";
} /// tests property ownership

void testJail() {
    Player player("Teodor");
    player.move_jail();
    assert(player.getPosition() == 9); /// the player is in jail
    assert(player.getJail() == 1);

    player.move_jail(); /// reduces the number of turns until the player can play again
    assert(player.getJail() == 2);

    player.move_jail(); /// the player can play again
    assert(player.getJail() == 0);
    std::cout << "jail passed\n";
}

void testTrain() {
    Player player("Teodor", 1500, 4); /// starting at a station
    player.move_train();

    assert(player.getPosition() == 12);
    player.move_train();
    assert(player.getPosition() == 24); /// the next stations
    player.move_train();
    assert(player.getPosition() == 32);

    player.move_train();
    assert(player.getPosition() == 4);
    /// checks that the player can loop through all stations, and at the last one, they will receive $200 for passing START
    std::cout << "train stations passed\n";
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); /// initialize seed for random

    // testPlayer();
    //testOwnership();
    //testJail();
    //testTrain();

    /// test the game itself for the functionality of the Turn function and board initialization
    Game game("players.txt", "board.txt"); /// generate the game using the files
    std::cout << '\n';
    game.Turn(0, 1);

    return 0;
}
