#pragma once
#include "Component.h"

class BlinkComponent : public Component
{
public:
    //点滅させるスプライトと点滅の間隔を受け取る
    BlinkComponent(class Actor* owner, class SpriteComponent* sprite, float blinkRate = 0.5f);

    void Update(float deltaTime) override;

private:
    class SpriteComponent* mSprite;
    float mBlinkRate;
    float mTimer;
};