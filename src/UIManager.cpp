#include "UIManager.h"
#include "Core/Game.h"
#include "Core/TextComponent.h"
#include "Core/BlinkComponent.h"

UIManager::UIManager(Game* game) : Actor(game), mScoreTextComp(nullptr), mFont(nullptr), mGameOverActor(nullptr),mStageClearActor(nullptr), mPromptActor(nullptr)
{
    //フォント読み込み
    mFont = TTF_OpenFont("../assets/dotto.ttf",36);

    if(!mFont)
    {
        SDL_Log("フォントの読み込み失敗:%s",TTF_GetError());
    }

    mScoreTextComp = new TextComponent(this);
    mScoreTextComp->SetFont(mFont);
    mScoreTextComp->SetColor({255, 255, 255, 255});

    SetPosition(130.0f, 40.0f);

    //初期スコアの表示
    UpdateScore(0);
}

UIManager::~UIManager()
{
    //使い終わったフォントは解放する
    if(mFont)
    {
        TTF_CloseFont(mFont);
    }
}

void UIManager::UpdateScore(int score)
{
    if(mScoreTextComp)
    {
        mScoreTextComp->SetText("Score: " + std::to_string(score));
    }
}

void UIManager::ShowGameOver()
{
    if(mGameOverActor || !mFont) return;

    mGameOverActor = new Actor(GetGame());
    mGameOverActor->SetPosition(400.0f, 300.0f);

    TextComponent* tc = new TextComponent(mGameOverActor);
    tc->SetFont(mFont);
    tc->SetColor({255, 0, 0, 255});
    tc->SetText("GAME OVER");
}

void UIManager::HideGameOver()
{
    //もしゲームオーバー文字が存在していれば
    if(mGameOverActor)
    {
        mGameOverActor->SetState(EDead);
        mGameOverActor = nullptr;
    }
}

void UIManager::ShowPrompt()
{
    if(mPromptActor || !mFont) return;

    mPromptActor = new Actor(GetGame());
    mPromptActor->SetPosition(400.0f, 400.0f);

    TextComponent* tc = new TextComponent(mPromptActor);
    tc->SetFont(mFont);
    tc->SetColor({255, 255, 255, 255});
    tc->SetText("Push -R- To RESTART");
}

void UIManager::HidePrompt()
{
    if(mPromptActor)
    {
        mPromptActor->SetState(EDead);
        mPromptActor = nullptr;
    }
}

void UIManager::ShowStageClear(int stage)
{
    if(mStageClearActor || !mFont) return;
    mStageClearActor = new Actor(GetGame());
    mStageClearActor->SetPosition(400.0f, 300.0f);

    TextComponent* tc = new TextComponent(mStageClearActor);
    tc->SetFont(mFont);
    tc->SetColor({255, 255, 0, 255});
    tc->SetText("STAGE " + std::to_string(stage) + " CLEAR!");

    new BlinkComponent(mStageClearActor, tc, 0.4f);
}

void UIManager::HideStageClear()
{
    if(mStageClearActor)
    {
        mStageClearActor->SetState(EDead);
        mStageClearActor = nullptr;
    }
}
