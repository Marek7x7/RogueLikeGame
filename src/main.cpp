#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>

#include "../include/battle_ui.hpp"
#include "../include/files.hpp"

int main(int argc, char* argv[]) {

    //getting variables to setup the save directory and file to save progress
    const char* homeDir = std::getenv("HOME");
    fs::path saveFile("saveFile.json");
    if (!homeDir) {
        std::cerr << "Could not find home directory." << std::endl;
        return 1;
    }
    std::string username;
    std::string userInput;

    //initializing username for the player
    std::cout << "Enter your username: ";
    std::getline(std::cin, username);

    //creating the file system to save the game
    checkSaveFile(homeDir, username);

    //loading player stats
    player pl = load();

    //initializing local player variables
    int hp = pl.hp;
    int mp = pl.mp;
    int damage = pl.damage;
    int speed = pl.speed;
    int defense = pl.defense;
    int level = pl.level;
    int xp = pl.xp;
    int playCount = pl.playCount;

    //checking if the player is new or not
    if (pl.playCount < 1) {
        std::cout << "Welcome to the game, " << username << "!\n";
        std::cout << "HP: " << hp << "\n";
        std::cout << "MP: " << mp << "\n";
        std::cout << "damage: " << damage << "\n";
        std::cout << "speed: " << speed << "\n";
        std::cout << "defense: " << defense << "\n";
    } else {
        std::cout << "Welcome Back " << username << "!\n";
    }

    
    //game loop
    while (userInput != "exit") {
        std::cout << "> ";
        std::getline(std::cin, userInput);

    if (userInput == "exit") {
        pl.username = username;
        pl.playCount += 1;
        save(pl, homeDir);
    }

        if (userInput == "battle") {
            // Create deque for enemies
            std::deque<Enemy> enemies;
            monsterGeneration(enemies, pl);
            runBattle(pl,enemies);
        }

    }

    return 0;
}