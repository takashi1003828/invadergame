#include "Core/MoveComponent.h"
#include "Core/Actor.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder) : Component(owner, updateOrder), mVelocityX(0.0f), mVelocityY(0.0f)
{
}

void MoveComponent::Update(float deltaTime)
{
    float x = mOwner->GetPositionX();
    float y = mOwner->GetPositionY();

    x += mVelocityX * deltaTime;
    y += mVelocityY * deltaTime;

    mOwner->SetPosition(x, y);
}