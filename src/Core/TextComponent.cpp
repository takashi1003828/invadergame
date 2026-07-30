#include "Core/TextComponent.h"
#include "Core/Actor.h"
#include "Core/Game.h"

TextComponent::TextComponent(Actor* owner, int drawOrder) : SpriteComponent(owner, drawOrder), mFont(nullptr), mColor({255, 255, 255, 255}), mTextTexture(nullptr)
{

}

TextComponent::~TextComponent()
{
    if(mTextTexture)
    {
        SDL_DestroyTexture(mTextTexture);
        mTextTexture = nullptr;
    }
}

void TextComponent::SetText(const std::string& text)
{
    if(mText != text)
    {
        mText = text;
        RecreateTexture();
    }
}

void TextComponent::SetFont(TTF_Font* font)
{
    mFont = font;
    RecreateTexture();
}

void TextComponent::SetColor(const SDL_Color& color)
{
    mColor = color;
    RecreateTexture();
}

void TextComponent::RecreateTexture()
{
    if(mTextTexture)
    {
        SDL_DestroyTexture(mTextTexture);
        mTextTexture = nullptr;
        SetTexture(nullptr);
    }

    if(!mFont || mText.empty())
    {
        return;
    }

    SDL_Surface* surf = TTF_RenderUTF8_Solid(mFont, mText.c_str(), mColor);
    if(!surf)
    {
        SDL_Log("Surface作成失敗: %s", TTF_GetError());
        return;
    }

    mTextTexture = SDL_CreateTextureFromSurface(mOwner->GetGame()->GetRenderer(), surf);
    SDL_FreeSurface(surf);

    if(mTextTexture)
    {
        SetTexture(mTextTexture);
    }
}

