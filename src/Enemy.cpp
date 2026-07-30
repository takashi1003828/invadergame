#include "Enemy.h"
#include "Core/SpriteComponent.h"
#include "Core/Game.h"
#include "Bullet.h"
#include "Core/CircleComponent.h"
#include "Core/MoveComponent.h"
#include "GameManager.h"

Enemy::Enemy(Game* game) : Actor(game)
{
    //画像をアタッチ
    SetScale(0.03f);
    SpriteComponent* sc = new SpriteComponent(this);
    //適用の画像読み込み
    SDL_Texture* tex = game->GetTexture("../assets/Player.png");
    sc->SetTexture(tex);

    //当たり判定をアタッチ　
    mCircle = new CircleComponent(this);
    mCircle->SetRadius(25.0f);

    //移動をアタッチ
    mMoveComp = new MoveComponent(this);
    //最初は右方向に毎秒150ピクセル
    mMoveComp->SetVelocity(150.0f, 0.0f);
}

void Enemy::SetSpeed(float speed)
{
    mMoveComp->SetVelocity(speed, 0.0f);
}

void Enemy::UpdateActor(float deltaTime)
{
    float x = GetPositionX();
    float y = GetPositionY();

    float currentVx = mMoveComp->GetVelocityX();
    //移動と壁に当たった時の反転
    if (x > 750.0f && mMoveComp->GetVelocityX() > 0.0f)
    {
        //左へ反転
        mMoveComp->SetVelocity(-currentVx, 0.0f);
        //Y座標に30ピクセル足して1段下げる
        SetPosition(x, y + 30.0f);
    }
    else if(x < 50.0f && mMoveComp->GetVelocityX() < 0.0f)
    {
        //速度をプラスにして右方向へ
        mMoveComp->SetVelocity(-currentVx, 0.0f);
        //1段下げる
        SetPosition(x, y + 30.0f);
    }

    //常に弾を観測
    const auto& actors = GetGame()->GetActors();
    for(auto actor : actors)
    {
        //アクターが弾なのかを判定する
        Bullet* b = dynamic_cast<Bullet*>(actor);

        if(b != nullptr)
        {
            //あたっていたら
            if(CircleComponent::Intersect(*mCircle, *(b->GetCircle())))
            {
                SetState(EDead);
                b->SetState(EDead);
                //スコア計算
                for(auto a : GetGame()->GetActors())
                {
                    GameManager* gm = dynamic_cast<GameManager*>(a);
                    if(gm != nullptr)
                    {
                        gm->AddScore(100);
                        break;
                    }
                }
                break;
            }
        }
    }
}