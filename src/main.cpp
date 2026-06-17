#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include "../include/json.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

 void writeSaveFile(std::string userName,const char* homeDir) {
    fs::path saveDirPath = fs::path(homeDir) / "Documents/repos/RogueLikeGame/save";
    fs::path saveFilePath = saveDirPath / "saveFile.json";
    json player;
    player["username"] = userName;
    player["level"] = 0;
    player["stats"]["hp"] = 10;
    player["stats"]["mp"] = 10;
    player["stats"]["speed"] = 1;
    player["stats"]["defense"] = 1;

    std::ofstream saveFile(saveFilePath);
    if (saveFile.is_open()) {
        saveFile << player.dump(4);
        saveFile.close();
    } else {
        std::cerr << "Failed to open the file." << std::endl;
    }

 }

void checkSaveFile (const char* homeDir, std::string userName) {
    fs::path saveDirPath = fs::path(homeDir) / "Documents/repos/RogueLikeGame/save";
    fs::path saveFilePath = saveDirPath / "saveFile.json";

    if (!fs::exists(saveDirPath)) {
        fs::create_directories(saveDirPath);
    }

    std::ofstream saveFile(saveFilePath);
    if (saveFile.is_open()) {
        writeSaveFile(userName, homeDir);
        saveFile.close();
    } else {
        std::cerr << "Failed to create the file." << std::endl;
    }
}

std::tuple<std::string, int, int, int, int, int> readSaveFile(const char* homeDir) {
    fs::path saveDirPath = fs::path(homeDir) / "Documents/repos/RogueLikeGame/save";
    fs::path saveFilePath = saveDirPath / "saveFile.json";

    std::ifstream saveFile(saveFilePath);

    if (!saveFile.is_open()) {
        std::cerr << "could not open save file." << std::endl;
    }

    json data = json::parse(saveFile);
    saveFile.close();

    std::string username = data["username"];
    int level = data["level"];
    int health = data["stats"]["hp"];
    int mana = data["stats"]["mp"];
    int speed = data["stats"]["speed"];
    int defense = data["stats"]["defense"];

    return std::make_tuple(username, level, health, mana, speed, defense);
 }



int main(int argc, char* argv[]) {
    //getting variables to setup the save directory and file to save progress
    const char* homeDir = std::getenv("HOME");
    fs::path saveFile("saveFile.json");
    if (!homeDir) {
        std::cerr << "Could not find home directory." << std::endl;
        return 1;
    }

    

    //asking user for username
    std::string userName;
    std::cout << "What is your username: ";;
    std::cin >> userName;
    //create save file if it doesn't exist and check if it can be created
    checkSaveFile(homeDir, userName);
    //read save file and store values in variables
    auto [username, level, health, mana, speed, defense] = readSaveFile(homeDir);

    

    return 0;
}
