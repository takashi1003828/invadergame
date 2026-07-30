#pragma once
#include "Core/Component.h"
#include <SDL2/SDL.h>

class SpriteComponent : public Component{
public:
    SpriteComponent(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent();

    virtual void Draw(SDL_Renderer* renderer);
    virtual void SetTexture(SDL_Texture* texture);

    void SetVisible(bool visible){mIsVisible = visible; }
    bool GetVisible() const { return mIsVisible; }

    int GetDrawOrder() const { return mDrawOrder; }
    int GetTexHeight() const { return mTexHeight; }
    int GetTexWidth() const { return mTexWidth; }

protected:
    SDL_Texture* mTexture;
    int mDrawOrder;
    int mTexWidth;
    int mTexHeight;
    bool mIsVisible = true;

};