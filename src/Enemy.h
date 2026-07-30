#pragma once
#include "Core/Actor.h"

class Enemy : public Actor
{
public:
    Enemy(class Game* game);
    void UpdateActor(float deltaTime) override;

    class CircleComponent* GetCircle() const { return mCircle; }

    void SetSpeed(float speed);

private:
    //当たり判定
    class CircleComponent* mCircle;
    //移動
    class MoveComponent* mMoveComp;
};