#include "Core/SpriteComponent.h"
#include "Core/Actor.h"
#include "Core/Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder) : Component(owner), mTexture(nullptr), mDrawOrder(drawOrder), mTexWidth(0), mTexHeight(0)
{
    //コンポーネント作成時にGameの描画リストに自身を追加
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent(){
    //破棄される時に描画リストから削除する
    mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer){
    if(mTexture){
        SDL_Rect r;
        r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
        r.h = static_cast<int>(mTexHeight * mOwner->GetScale());

        r.x = static_cast<int>(mOwner->GetPositionX() - r.w / 2);
        r.y = static_cast<int>(mOwner->GetPositionY() - r.h /2);

        

        //SDLの関数を利用して画面に描画する
        SDL_RenderCopyEx(renderer, mTexture, nullptr, &r, 0.0, nullptr, SDL_FLIP_NONE);
        
    } else {
        SDL_Log("Draw実行 mTextureがnullptrです。");
    }
}

void SpriteComponent::SetTexture(SDL_Texture* texture){
    mTexture = texture;
    //テクスチャがセットされたら幅と高さを取得する
    SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}