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

    //initializing username for the player
    std::string username;
    std::cout << "Enter your username: ";
    std::getline(std::cin, username);

    //creating the file system to save the game
    checkSaveFile(homeDir, username);

    //loading player stats
    player pl = load();

    if (pl.playCount < 1) {
        std::cout << "Welcome to the game, " << pl.username << "!\n";
        std::cout << "HP: " << pl.hp << "\n";
        std::cout << "MP: " << pl.mp << "\n";
        std::cout << "speed: " << pl.speed << "\n";
        std::cout << "defense: " << pl.defense << "\n";
    } else {
        std::cout << "Welcome Back" << pl.username << "!\n";
    }

    return 0;
}

