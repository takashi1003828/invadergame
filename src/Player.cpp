#include "Player.h"
#include "Core/SpriteComponent.h"
#include "Core/Game.h"

Player::Player(Game* game) : Actor(game){
    //画面の中央したあたりに座標をセット（仮）
    SetPosition(400.0f, 500.0f);

    //スプライトコンポーネントのスケールを設定
    SetScale(0.05f);
    //自分のActorにスプライトを取り付け
    SpriteComponent* sc = new SpriteComponent(this);

    //画像を読み込んでコンポーネントにセット
    SDL_Texture* tex = game->GetTexture("../assets/Player.png");
    sc->SetTexture(tex);
}

void Player::UpdateActor(float deltaTime){
    //移動処理
}