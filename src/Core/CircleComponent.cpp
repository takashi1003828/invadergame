#include "Core/CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor* owner) : Component(owner), mRadius(0.0f)
{ 
}

bool CircleComponent::Intersect(const CircleComponent& a, const CircleComponent& b)
{
    float dx = a.GetOwner()->GetPositionX() - b.GetOwner()->GetPositionX();
    float dy = a.GetOwner()->GetPositionY() - b.GetOwner()->GetPositionY();

    //距離の2乗を計算
    float distSq = dx * dx + dy * dy;

    float radiiSq = a.GetRadius() + b.GetRadius();
    radiiSq *= radiiSq;

    return distSq <= radiiSq;
}