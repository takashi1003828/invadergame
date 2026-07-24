#pragma once
#include "Core/Actor.h"

class Enemy : public Actor
{
public:
    Enemy(class Game* game);
    void UpdateActor(float deltaTime) override;

    class CircleComponent* GetCircle() const { return mCircle; }

private:
    class CircleComponent* mCircle;
};