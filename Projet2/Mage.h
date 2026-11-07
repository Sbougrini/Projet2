// Andy Donero
#pragma once

#include <vector>

#include "Player.h"

class Map;

class Mage : public virtual Player
{
public:
    static constexpr char SYMBOL = 'M';
    static constexpr int MAX_HEALTH = 1;
    static constexpr char SPELL_KEY = ' ';

    Mage(const Vector2 &startPosition);

    void onUpdate(const Map &map, const std::vector<Entity *> &entities) override;
    void onCollision(Entity *other) override;
    char getSymbol() const override;
    bool canCastSpell() const override;

    void castSpell(const std::vector<Entity *> &entities);

private:
    static constexpr char SPELL_SYMBOL = '*';
    static constexpr int SPELL_DISPLAY_MS = 300;
    void showSpellArea() const;
};

inline char Mage::getSymbol() const
{
    return SYMBOL;
}

inline bool Mage::canCastSpell() const
{
    return true;
}