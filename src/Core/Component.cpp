#include "Core/Component.h"
#include "Core/Actor.h"

Component::Component(Actor* owner, int updateOrder) : mOwner(owner), mUpdateOrder(updateOrder)
{
    //自分自身をOwnerのコンポーネントリストに追加する処理
    mOwner->AddComponent(this);
}

Component::~Component(){
    //ここで自信をOwnerのリストから削除する処理
    mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime){
    //何もしない。継承先で具体的な処理を書く
}