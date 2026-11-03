// Andy Donero
#pragma once

#include "Mage.h"
#include "Warrior.h"

class WarriorMage : public Warrior, public Mage
{
public:
    WarriorMage(const Vector2 &startPosition);

    char getSymbol() const override;
    void onEnemyCollision(Enemy &enemy) override;
};
