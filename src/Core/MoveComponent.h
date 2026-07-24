#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
    MoveComponent(class Actor* owner, int updateOrder = 10);
    void Update(float deltaTime) override;

    //縦横の移動スピードをセット・ゲットする関数
    void SetVelocity(float vx, float vy) { mVelocityX = vx; mVelocityY = vy; }

    float GetVelocityX() const { return mVelocityX; }
    float GetVelocityY() const { return mVelocityY; }

private:
    //1秒間に進むピクセル数
    float mVelocityX;
    float mVelocityY;
};