#pragma once
#include "Core/Component.h"
#include <SDL2/SDL.h>

class InputComponent : public Component {
public :
    InputComponent(class Actor* owner, int updateOrder = 100);

    //マイフレームの更新処理をオーバーライド
    void Update(float deltaTime) override;

    //前後移動の速度
    void SetMaxForwardSpeed(float speed) {mMaxForwardSpeed = speed; }
    float GetMaxForwardSpeed() const { return mMaxForwardSpeed; }

    //左右移動の速度
    void SetMaxRightSpeed(float speed) {mMaxRightSpeed = speed; }
    float GetMaxRightSpeed() const { return mMaxRightSpeed; }

    //キー割当て用の設定関数
    void SetForwardKey(int key) { mForwardKey = key; }
    void SetBackKey(int key) {mBackKey = key; }
    void SetRightKey(int key) {mRightKey = key;}
    void SetLeftKey(int key) {mLeftKey = key; }

private :
    //スピードの設定値
    float mMaxForwardSpeed;
    float mMaxRightSpeed;

    //割り当てるキーボードのキー
    int mForwardKey;
    int mBackKey;
    int mRightKey;
    int mLeftKey;
};