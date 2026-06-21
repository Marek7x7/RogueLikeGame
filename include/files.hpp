#pragma once
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "json.hpp"
#include "player.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

inline player load() {
    fs::path saveDirPath = fs::path(std::getenv("HOME")) / "Documents/repos/RogueLikeGame/save";
    fs::path saveFilePath = saveDirPath / "saveFile.json";

    std::ifstream saveFile(saveFilePath);

    json data = json::parse(saveFile);
    saveFile.close();

    player pl;
    pl.username = data["username"];
    pl.playCount = data["playCount"];
    pl.level = data["stats"]["level"];
    pl.hp = data["stats"]["hp"];
    pl.mp = data["stats"]["mp"];
    pl.damage = data["stats"]["damage"];
    pl.speed = data["stats"]["speed"];
    pl.defense = data["stats"]["defense"];

    return pl;
}

inline void save(const player &pl, const char* homeDir) {
    fs::path saveDirPath = fs::path(homeDir) / "Documents/repos/RogueLikeGame/save";
    fs::path saveFilePath = saveDirPath / "saveFile.json";
    json playerData;
    playerData["username"] = pl.username;
    playerData["playCount"] = pl.playCount;
    playerData["stats"]["level"] = pl.level;
    playerData["stats"]["hp"] = pl.hp;
    playerData["stats"]["mp"] = pl.mp;
    playerData["stats"]["damage"] = pl.damage;
    playerData["stats"]["speed"] = pl.speed;
    playerData["stats"]["defense"] = pl.defense;

    std::ofstream saveFile(saveFilePath);
    if (saveFile.is_open()) {
        saveFile << playerData.dump(4);
        saveFile.close();
    } else {
        std::cerr << "Failed to open the file." << std::endl;
    }
}

inline void checkSaveFile(const char* homeDir, std::string username) {
    fs::path saveDirPath = fs::path(homeDir) / "Documents/repos/RogueLikeGame/save";
    fs::path saveFilePath = saveDirPath / "saveFile.json";

    if (!fs::exists(saveDirPath)) {
        fs::create_directories(saveDirPath);
    }

    if (!fs::exists(saveFilePath)) {
        player defaultPlayer;
        defaultPlayer.username = username;
        save(defaultPlayer, homeDir);
    }

}

