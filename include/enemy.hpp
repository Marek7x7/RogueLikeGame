#pragma once

#include <string>

struct enemy_stats
{
    struct goblin
    {
        static const int hp = 10;
        static const int mp = 0;
        static const int damage = 2;
        static const int defense = 1;
        static const int speed = 1;
        static const int reward = 1;
    };
    
    struct orc
    {
        static const int hp = 35;
        static const int mp = 0;
        static const int damage = 8;
        static const int defense = 3;
        static const int speed = 2;
        static const int reward = 2;
    };
    
    struct troll
    {
        static const int hp = 50;
        static const int mp = 0;
        static const int damage = 12;
        static const int defense = 5;
        static const int speed = 1;
        static const int reward = 3;
    };
};

// This will be used in battle system to provide a way to access enemy stats
struct Enemy {
    std::string name;
    int hp;
    int maxHp;
    int damage;
    int speed;
    int xpReward;
    
    // Constructor for goblin
    Enemy(const enemy_stats::goblin&) : 
        name("Goblin"),
        hp(enemy_stats::goblin::hp),
        maxHp(enemy_stats::goblin::hp),
        damage(enemy_stats::goblin::damage),
        speed(enemy_stats::goblin::speed),
        xpReward(enemy_stats::goblin::reward * 10) {}
    
    // Constructor for orc
    Enemy(const enemy_stats::orc&) : 
        name("Orc"),
        hp(enemy_stats::orc::hp),
        maxHp(enemy_stats::orc::hp),
        damage(enemy_stats::orc::damage),
        speed(enemy_stats::orc::speed),
        xpReward(enemy_stats::orc::reward * 15) {}
    
    // Constructor for troll
    Enemy(const enemy_stats::troll&) : 
        name("Troll"),
        hp(enemy_stats::troll::hp),
        maxHp(enemy_stats::troll::hp),
        damage(enemy_stats::troll::damage),
        speed(enemy_stats::troll::speed),
        xpReward(enemy_stats::troll::reward * 20) {}
    
    // Default constructor
    Enemy() : hp(0), maxHp(0), damage(0), speed(0), xpReward(0) {}

    bool isAlive() const { return hp > 0; }
};