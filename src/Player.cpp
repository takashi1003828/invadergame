#include "Player.h"
#include "Core/SpriteComponent.h"
#include "Core/Game.h"
#include "Core/InputComponent.h"
#include "Bullet.h"

Player::Player(Game* game) : Actor(game), mCooldown(0.0f)
{
    //画面の中央したあたりに座標をセット（仮）
    SetPosition(400.0f, 500.0f);

    //スプライトコンポーネントのスケールを設定
    SetScale(0.05f);
    //自分のActorにスプライトを取り付け
    SpriteComponent* sc = new SpriteComponent(this);

    //画像を読み込んでコンポーネントにセット
    SDL_Texture* tex = game->GetTexture("../assets/Player.png");
    sc->SetTexture(tex);

    InputComponent* ic = new InputComponent(this);

    //インベーダーゲームなので左右移動のみ
    //速度を秒間300ピクセルとする。
    ic->SetMaxRightSpeed(300.0f);
}

void Player::UpdateActor(float deltaTime)
{
    mCooldown -= deltaTime;

    const Uint8* state = SDL_GetKeyboardState(NULL);

    if(state[SDL_SCANCODE_SPACE] && mCooldown <= 0.0f)
    {
        Bullet* b = new Bullet(GetGame());

        b->SetPosition(GetPositionX(), GetPositionY());

        mCooldown = 0.25f;
    }
}