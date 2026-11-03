// Andy Donero
#pragma once

#include "Player.h"

class Enemy;
class Game;

class Mage : public virtual Player
{
public:
    Mage(const Vector2 &startPosition);

    char getSymbol() const override;
    void onEnemyCollision(Enemy &enemy) override;
    bool useSpecial(Game &game) override;
};