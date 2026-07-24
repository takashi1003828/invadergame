#include "Bullet.h"
#include "Core/SpriteComponent.h"
#include "Core/MoveComponent.h"
#include "Core/Game.h"
#include "Core/CircleComponent.h"

Bullet::Bullet(Game* game) : Actor(game)
{
    SetScale(0.005f);
    SpriteComponent* sc = new SpriteComponent(this);
    //一旦テクスチャ使い回し
    SDL_Texture* tex = game->GetTexture("../assets/Player.png");
    sc->SetTexture(tex);

    //当たり判定
    mCircle = new CircleComponent(this);
    mCircle->SetRadius(10.0f);

    //移動パーツ
    MoveComponent* mc = new MoveComponent(this);
    //弾は上向きに
    mc->SetVelocity(0.0f, -400.0f);
}

void Bullet::UpdateActor(float delataTime)
{
    //メモリリーク対策
    if (GetPositionY() < -50.0f)
    {
        SetState(EDead);
    }
}
