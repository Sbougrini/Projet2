// Sami Bougrini
#pragma once
class Swimmer
{
public:
    virtual ~Swimmer() = 0;
    static constexpr int MAX_OXYGEN = 3;
    void updateOxygen(bool isInWater);
    bool hasOxygen() const;

private:
    int oxygen = MAX_OXYGEN;
};