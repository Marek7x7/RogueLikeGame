#pragma once
#include <string>

struct player
{
    std::string username;
    int level = 0;
    int hp = 10;
    int mp = 10;
    int damage = 3;
    int speed = 1;
    int defense = 1;
    int playCount = 0;
};