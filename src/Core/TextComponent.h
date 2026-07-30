#pragma once
#include "SpriteComponent.h"
#include <SDL2/SDL_ttf.h>
#include <string>

class TextComponent : public SpriteComponent
{
public:
    TextComponent(class Actor* owner, int drawOrder = 100);
    ~TextComponent();

    void SetText(const std::string& text);
    void SetFont(TTF_Font* font);
    void SetColor(const SDL_Color& color);

    const std::string& GetText() const {return mText; }

private:
    void RecreateTexture();

    std::string mText;
    TTF_Font* mFont;
    SDL_Color mColor;

    SDL_Texture* mTextTexture;
};