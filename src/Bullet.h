#pragma once
#include "Core/Actor.h"

class Bullet : public Actor 
{
public:
    Bullet(class Game* game);
    //外部から当たり判定を取得できる
    class CircleComponent* GetCircle() const {return mCircle; }

    //球が画面外に出たかの判定用
    void UpdateActor(float deltaTime) override;

private:
    class CircleComponent* mCircle;
};