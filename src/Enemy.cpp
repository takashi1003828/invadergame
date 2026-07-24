#include "Enemy.h"
#include "Core/SpriteComponent.h"
#include "Core/Game.h"
#include "Bullet.h"
#include "Core/CircleComponent.h"

Enemy::Enemy(Game* game) : Actor(game)
{
    SetScale(0.03f);
    SpriteComponent* sc = new SpriteComponent(this);
    //適用の画像読み込み
    SDL_Texture* tex = game->GetTexture("../assets/Player.png");
    sc->SetTexture(tex);

    //当たり判定をアタッチ　
    mCircle = new CircleComponent(this);
    mCircle->SetRadius(25.0f);
}

void Enemy::UpdateActor(float deltaTime)
{
    //やられ判定
    const auto& actors = GetGame()->GetActors();
    for(auto actor : actors)
    {
        //アクターが弾なのかを判定する
        Bullet* b = dynamic_cast<Bullet*>(actor);

        if(b != nullptr)
        {
            //弾かつあたっていたら
            if(CircleComponent::Intersect(*mCircle, *(b->GetCircle())))
            {
                SetState(EDead);

                b->SetState(EDead);

                break;
            }
        }
    }
}