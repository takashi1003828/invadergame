#include "Core/Actor.h"
#include "Core/Component.h"
#include "Core/Game.h"
#include <algorithm>

Actor::Actor(Game* game) : mState(EActive), mPositionX(0.0f), mPositionY(0.0f),mScale(1.0f), mGame(game)
{
    //作られたらGameクラス内の配列に自分を登録
    mGame->AddActor(this);
}

Actor::~Actor(){
    //死んだら上記の配列から削除
    mGame->RemoveActor(this);
    //自分が破壊される時に持っているコンポーネントも全てメモリから解放する
    while (!mComponents.empty()){
        delete mComponents.back();
    }
}

//アクターについているパーツの更新
void Actor::UpdateComponents(float deltaTime){
    for(auto comp : mComponents){
        comp->Update(deltaTime);
    }
}

//更新処理
void Actor::Update(float deltaTime){
    if(mState == EActive)
    {
        UpdateComponents(deltaTime);

        UpdateActor(deltaTime);
    }
}

//パーツを追加する
void Actor::AddComponent(Component* component){
    int myOrder = component->GetUpdateOrder();
    auto iter = mComponents.begin();
    for(; iter != mComponents.end(); ++iter){
        if(myOrder < (*iter)->GetUpdateOrder()){
            break;
        }
    }
    mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component){
    auto iter = std::find(mComponents.begin(), mComponents.end(),component);
    if (iter != mComponents.end()){
        mComponents.erase(iter);
    }
}

void Actor::UpdateActor(float deltaTime){
    //中身は後で
}