#pragma once
#include <iostream>
#include <sstream>
#include <deque>
#include <string>
#include <cctype>
#include "player.hpp"
#include "battle.hpp"

//HELPERS

// battle_ui.hpp — add near the other helpers
inline void clearScreen() {
    std::cout << "\033[2J\033[1;1H" << std::flush;
}

// Lowercase a string (for case-insensitive command matching)
inline std::string toLower(std::string s) {
    for (char& c : s) c = static_cast<char>(std::tolower(c));
    return s;
}

// Prints: [1] Goblin | [2] Orc | [3] Troll
inline void printEnemyList(const std::deque<Enemy>& enemies) {
    for (size_t i = 0; i < enemies.size(); ++i) {
        std::cout << "[" << (i + 1) << "] " << enemies[i].name << " [HP: " << enemies[i].hp << "]";
        if (i + 1 < enemies.size()) std::cout << " | ";
    }
    std::cout << "\n";
}

inline void printActionBar() {
    std::cout << "actions: (a)ttack <n> | (f)lee | (i)nventory\n";
    std::cout << "> ";
}

// Main battle UI loop
inline BattleStatus runBattle(player& pl, std::deque<Enemy>& enemies) {
    std::string line;

    while (getBattleStatus(pl, enemies) == BattleStatus::Ongoing) {
        printEnemyList(enemies);
        printActionBar();
        clearScreen();

        if (!std::getline(std::cin, line)) break; // EOF / input failure safety

        std::istringstream iss(line);
        std::string command;
        iss >> command;
        command = toLower(command);

        if (command.empty()) {
            std::cout << "Enter a command.\n\n";
            continue;
        }

        // ---- ATTACK ----
        if (command == "a" || command == "attack") {
            int targetNum;
            if (!(iss >> targetNum)) {
                std::cout << "Usage: a <n>  (e.g. 'a 1')\n\n";
                continue;
            }

            AttackResult result = attackEnemy(pl, enemies, targetNum - 1);

            switch (result.outcome) {
                case AttackOutcome::InvalidTarget:
                    std::cout << "No enemy at that number.\n";
                    break;

                case AttackOutcome::TargetAlreadyDead:
                    std::cout << "That enemy is already defeated.\n";
                    break;

                case AttackOutcome::Hit:
                    std::cout << "You hit the " << result.enemyName
                               << " for " << result.damageDealt << " damage.\n";

                    if (result.enemyDefeated) {
                        std::cout << "The " << result.enemyName << " was defeated!\n";
                    }

                    if (result.enemyCounterattacked) {
                        std::cout << "The " << result.enemyName
                                   << " hits you for " << result.damageTaken
                                   << " damage. (HP: " << pl.hp << ")\n";
                    }

                    if (result.playerDefeated) {
                        std::cout << "You have been defeated!\n";
                    }
                    break;
            }
            std::cout << "\n";
        }
        // ---- FLEE ----
        else if (command == "f" || command == "flee") {
            std::cout << "You fled from battle!\n\n";
            return BattleStatus::Fled;
        }
        // ---- INVENTORY (placeholder, not built yet) ----
        else if (command == "i" || command == "inventory") {
            std::cout << "Inventory not implemented yet.\n\n";
        }
        // ---- INVALID ----
        else {
            std::cout << "Unknown command: " << command << "\n\n";
        }
    }

    BattleStatus finalStatus = getBattleStatus(pl, enemies);

    if (finalStatus == BattleStatus::Victory) {
        std::cout << "All enemies defeated! You won the battle!\n";
    } else if (finalStatus == BattleStatus::Defeat) {
        std::cout << "You have been defeated...\n";
    }

    return finalStatus;
}
