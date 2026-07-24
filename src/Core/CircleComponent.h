#pragma once
#include "Component.h"

class CircleComponent : public Component
{
public:
    CircleComponent(class Actor* owner);

    //半径のセットとゲット
    void SetRadius(float radius) {mRadius = radius; }
    float GetRadius() const { return mRadius; }

    static bool Intersect(const CircleComponent& a, const CircleComponent& b);

private:
    float mRadius;
};