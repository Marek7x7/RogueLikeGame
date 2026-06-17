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

    std::string username;
    std::cout << "Enter your username: ";
    std::getline(std::cin, username);
    
    checkSaveFile(homeDir, username);

    player pl = load();

    std::cout << "Welcome to the game, " << pl.username << "!\n";
    std::cout << "HP: " << pl.hp << "\n";

    return 0;
}

