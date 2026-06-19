#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include "../include/json.hpp"
#include "../include/player.hpp"
#include "../include/game.hpp"

int main(int argc, char* argv[]) {

    //getting variables to setup the save directory and file to save progress
    const char* homeDir = std::getenv("HOME");
    fs::path saveFile("saveFile.json");
    if (!homeDir) {
        std::cerr << "Could not find home directory." << std::endl;
        return 1;
    }
    //creating the file system to save the game
    checkSaveFile(homeDir, "user");


    std::string username;
    std::string userInput;

    //initializing username for the player
    std::cout << "Enter your username: ";
    std::getline(std::cin, username);

    //loading player stats
    player pl = load();

    //initializing local player variables
    int hp = pl.hp;
    int mp = pl.mp;
    int speed = pl.speed;
    int defense = pl.defense;
    int level = pl.level;
    int playCount = pl.playCount;

    //checking if the player is new or not
    if (pl.playCount < 1) {
        std::cout << "Welcome to the game, " << username << "!\n";
        std::cout << "HP: " << hp << "\n";
        std::cout << "MP: " << mp << "\n";
        std::cout << "speed: " << speed << "\n";
        std::cout << "defense: " << defense << "\n";
    } else {
        std::cout << "Welcome Back" << username << "!\n";
    }

    
    //game loop
    while (userInput != "exit") {
        std::cout << "write exit" << "\n";
        std::getline(std::cin, userInput);

        if (userInput == "exit") {
            pl.username = username;
            pl.hp = hp;
            pl.mp = mp;
            pl.speed = speed;
            pl.defense = defense;
            pl.level = defense;
            pl.playCount = playCount += 1;
            save(pl, homeDir);
        }
    }

    return 0;
}

