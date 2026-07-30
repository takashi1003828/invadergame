#pragma once
#include "Core/Actor.h"
#include <string>
#include <SDL2/SDL_ttf.h>

class TextComponent;

class UIManager : public Actor
{
public:
    UIManager(class Game* game);
    ~UIManager();

    //スコア更新
    void UpdateScore(int score);

    void ShowGameOver();
    void HideGameOver();

    void ShowStageClear(int stage);
    void HideStageClear();

    void ShowPrompt();
    void HidePrompt();

private:
    TextComponent* mScoreTextComp;

    class Actor* mGameOverActor;
    class Actor* mStageClearActor;
    class Actor* mPromptActor;

    //読み込んだフォントデータ
    TTF_Font* mFont;
};
