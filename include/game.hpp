#pragma once
#include <iostream>
#include <random>

#include "player.hpp"
#include "enemy.hpp"

int generateNumber () {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 100);
    int number = distr(gen);
    return number;
}


void battle (const player &pl, const enemy, std::string userInput) {
    if (pl.level < 2) {
        std::cout << "you are fighting a goblin" << "\n";
        enemy::goblin gobling;

        while (!gobling.hp <= 0 || !pl.hp <= 0) {
            std::cout << "(a)ttack | (f)lee" << "\n";
            std::cout << "> ";
            std::getline(std::cin, userInput);

            if (userInput == "a") {
                if (pl.speed < gobling.speed) {
                    pl.hp - gobling.damage;
                    std::cout << "the gobling did " << gobling.damage << " to you" << "\n";
                } else if (pl.speed >= gobling.speed) {
                    gobling.hp - pl.damage;
                    std::cout << "you did " << pl.damage << " to the gobling" << "\n";
                }
                
            } else if (userInput == "f") {
                break;
            } else {
                std::cout << "the command: " << userInput << " isnt valid" << "\n";
            }
        }
        std::cout << "end of battle" << "\n";
    }
}

