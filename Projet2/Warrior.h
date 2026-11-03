// Andy Donero
#pragma once

#include "Player.h"

class Enemy;

class Warrior : public virtual Player
{
public:
    Warrior(const Vector2 &startPosition);

    char getSymbol() const override;
    void onEnemyCollision(Enemy &enemy) override;
};
