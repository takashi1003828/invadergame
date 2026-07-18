#pragma once

class Actor;

class Component{
public:
    //コンストラクタ
    //updateOrderは更新の優先順位
    Component(Actor* owner, int updateOrder = 100);

    //仮想デストラクタ（継承先で正しく破棄されるため）
    virtual ~Component();

    virtual void Update(float deltaTime);

    Actor* GetOwner() const {return mOwner; }

    int GetUpdateOrder() const { return mUpdateOrder; }

protected:
    Actor* mOwner;
    int mUpdateOrder;
};