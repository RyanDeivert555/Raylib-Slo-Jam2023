#pragma once
#include "spaceship.h"

class Player : public Spaceship {
private:
    bool _warnNoShield = false;
    float _maxWarningTimer = 3.0f;
    float _warningTimer = _maxWarningTimer;

    void getInput();
    void warnNoShields();
    
public:
    static constexpr float Acceleration = 200.0f;
    static constexpr float MaxSpeed = 700.0f;
    static constexpr float MinSpeed = 150.0f;

    Player(std::size_t id);
    void Reset();
    void Update() override;
    void DrawShieldWarning() const;
};