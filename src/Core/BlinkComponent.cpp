#include "Core/BlinkComponent.h"
#include "SpriteComponent.h"

BlinkComponent::BlinkComponent(Actor* owner, SpriteComponent* sprite, float blinkRate) : Component(owner), mSprite(sprite), mBlinkRate(blinkRate), mTimer(0.0f)
{
}

void BlinkComponent::Update(float deltaTime)
{
    if(!mSprite) return;

    mTimer += deltaTime;
    
    if(mTimer >= mBlinkRate)
    {
        mTimer = 0.0f;
        mSprite->SetVisible(!mSprite->GetVisible());
    }
}