#include "Core/InputComponent.h"
#include "Core/Actor.h"

InputComponent::InputComponent(Actor* owner, int updateOrder) : Component(owner, updateOrder), mMaxForwardSpeed(0.0f), mMaxRightSpeed(0.0f), mForwardKey( SDL_SCANCODE_W), mBackKey( SDL_SCANCODE_S), mRightKey( SDL_SCANCODE_D), mLeftKey(SDL_SCANCODE_A)
{

} 

void InputComponent::Update(float deltaTime)
{
    //SDLから現在のキーボードの押下状態を一括取得
    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    float forwardSpeed = 0.0f;
    float rightSpeed = 0.0f;

    //キー入力に応じた速度決定
    if (keyState[mForwardKey])
    {
        forwardSpeed -= mMaxForwardSpeed;
    }
    if (keyState[mBackKey])
    {
        forwardSpeed += mMaxForwardSpeed;
    }
    if (keyState[mRightKey])
    {
        rightSpeed += mMaxRightSpeed;
    }
    if (keyState[mLeftKey])
    {
        rightSpeed -= mMaxRightSpeed;
    }

    //Actorの座標を更新する。

    float posX = mOwner->GetPositionX();
    float posY = mOwner->GetPositionY();

    posX += rightSpeed * deltaTime;
    posY += forwardSpeed * deltaTime;

    //新しい座標をActorにセット
    mOwner->SetPosition(posX, posY);
}