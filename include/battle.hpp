#pragma once
#include <random>
#include <deque>
#include <string>
#include "player.hpp"
#include "enemy.hpp"


inline int generateNumber() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 100);
    return distr(gen);
}

inline void monsterGeneration(std::deque<Enemy>& enemies, const player& pl) {
    enemies.clear();

    int enemyCount = 1 + (pl.level / 3);

    for (int i = 0; i < enemyCount; ++i) {
        int monsterType = generateNumber();

        if (monsterType <= 60) {
            Enemy goblin;
            goblin.name = "Goblin";
            goblin.hp = 10 + (pl.level * 2);
            goblin.maxHp = goblin.hp;
            goblin.damage = 2 + pl.level;
            goblin.speed = 3 + (pl.level / 2);
            goblin.xpReward = 10 + pl.level;
            enemies.push_back(goblin);
        }
        else if (monsterType <= 90) {
            Enemy orc;
            orc.name = "Orc";
            orc.hp = 35 + (pl.level * 3);
            orc.maxHp = orc.hp;
            orc.damage = 8 + pl.level;
            orc.speed = 2 + (pl.level / 3);
            orc.xpReward = 15 + pl.level * 2;
            enemies.push_back(orc);
        }
        else {
            Enemy troll;
            troll.name = "Troll";
            troll.hp = 50 + (pl.level * 4);
            troll.maxHp = troll.hp;
            troll.damage = static_cast<int>(12 + pl.level * 1.5);
            troll.speed = 1 + (pl.level / 4);
            troll.xpReward = 20 + pl.level * 3;
            enemies.push_back(troll);
        }
    }
}


enum class AttackOutcome {
    InvalidTarget,      // index out of range
    TargetAlreadyDead,  // tried to hit a corpse
    Hit                 // attack went through (check fields below for what happened)
};

struct AttackResult {
    AttackOutcome outcome = AttackOutcome::InvalidTarget;

    std::string enemyName;     // which enemy was targeted
    int damageDealt = 0;       // damage player did to enemy
    bool enemyDefeated = false;

    bool enemyCounterattacked = false; // false if enemy died before it could hit back
    int damageTaken = 0;               // damage enemy did to player
    bool playerDefeated = false;       // true if this attack brought player to 0 hp
};

enum class BattleStatus {
    Ongoing,
    Victory,   // all enemies defeated
    Defeat,    // player hp <= 0
    Fled       // player chose to flee
};


// Player attacks enemy at targetIndex. Mutates pl and enemies.
// Returns a result struct describing exactly what happened —
// no printing, no input reading.
inline AttackResult attackEnemy(player& pl, std::deque<Enemy>& enemies, int targetIndex) {
    AttackResult result;

    if (targetIndex < 0 || static_cast<size_t>(targetIndex) >= enemies.size()) {
        result.outcome = AttackOutcome::InvalidTarget;
        return result;
    }

    Enemy& target = enemies[targetIndex];

    if (!target.isAlive()) {
        result.outcome = AttackOutcome::TargetAlreadyDead;
        return result;
    }

    result.outcome = AttackOutcome::Hit;
    result.enemyName = target.name;

    // player hits enemy
    target.hp -= pl.damage;
    result.damageDealt = pl.damage;

    if (target.hp <= 0) {
        result.enemyDefeated = true;
        enemies.erase(enemies.begin() + targetIndex);
    } else {
        // enemy hits back (bug fixed: this used to compute and discard the value)
        result.enemyCounterattacked = true;
        result.damageTaken = target.damage;
        pl.hp -= target.damage;

        if (pl.hp <= 0) {
            result.playerDefeated = true;
        }
    }

    return result;
}

// Call this any time you want to know whether the battle is over,
// and why. Drive your UI's state machine off this.
inline BattleStatus getBattleStatus(const player& pl, const std::deque<Enemy>& enemies) {
    if (pl.hp <= 0) return BattleStatus::Defeat;
    if (enemies.empty()) return BattleStatus::Victory;
    return BattleStatus::Ongoing;
}

inline int getXpReward(const Enemy& e) {
    return e.xpReward;
}