#include "GameManager.h"
#include "Core/Game.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "SpawnManager.h"
#include "UIManager.h"
#include<SDL2/SDL.h>

GameManager::GameManager(Game* game) : Actor(game), mScore(0), mIsGameOver(false), mIsStageCleared(false), mCurrentStage(1)
{
    mUIManager = new UIManager(game);
}

void GameManager::UpdateActor(float deltaTime)
{
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (mIsGameOver)
    {
        if(state[SDL_SCANCODE_R])
        {
            mIsGameOver = false;

            mScore = 0;
            mCurrentStage = 1;
            mUIManager->UpdateScore(mScore);
            mUIManager->HideGameOver();
            mUIManager->HidePrompt();

            const auto& actors = GetGame()->GetActors();

            //メモリをリセットする
            for(auto actor : actors)
            {
                if(dynamic_cast<Player*>(actor) || dynamic_cast<Enemy*>(actor) || dynamic_cast<Bullet*>(actor))
                {
                    actor->SetState(EDead);
                }
            }

            //SpawnManagerを探し新しいキャラを再生成
            for(auto actor : actors)
            {
                SpawnManager* sm = dynamic_cast<SpawnManager*>(actor);
                if(sm)
                {
                    sm->Reset();
                    break;
                }
            }
        }
        return;
    }

    if(mIsStageCleared)
    {
        if(state[SDL_SCANCODE_R])
        {
            mIsStageCleared = false;
            mCurrentStage++;

            mUIManager->HideStageClear();
            mUIManager->HidePrompt();

            const auto& actors = GetGame()->GetActors();

            for(auto actor : actors)
            {
                if(dynamic_cast<Player*>(actor) || dynamic_cast<Bullet*>(actor))
                {
                    actor->SetState(EDead);
                }
            }
            for(auto actor : actors)
            {
                SpawnManager* sm = dynamic_cast<SpawnManager*>(actor);
                if(sm)
                {
                    sm->NextStage();
                    break;
                }    
            }
        }
        return;
    }

    const auto& actors = GetGame()->GetActors();
    bool enemyExists = false;

    for (auto actor : actors)
    {
        Enemy* enemy = dynamic_cast<Enemy*>(actor);
        if(enemy != nullptr)
        {
            enemyExists = true;

            if(enemy->GetPositionY() > 450.0f)
            {
                mIsGameOver = true;
                SDL_Log("===GAME OVER ==");
                SDL_Log("Final Score: %d", mScore);

                mUIManager->ShowGameOver();
                mUIManager->ShowPrompt();
                //全てのアクターをEPausedにする
                for(auto a : actors)
                {
                    if(dynamic_cast<Player*>(a) || dynamic_cast<Enemy*>(a) || dynamic_cast<Bullet*>(a))
                    {
                        a->SetState(EPaused);
                    }
                }
                break;
            }
        }
    }

    if(!enemyExists && !mIsGameOver)
    {
        SDL_Log("===STAGE CLEAR====");
        mIsStageCleared = true;
        mUIManager->ShowStageClear(mCurrentStage);
        mUIManager->ShowPrompt();

        for(auto a : actors)
        {
            if(dynamic_cast<Player*>(a) || dynamic_cast<Bullet*>(a))
            {
                a->SetState(EPaused);
            }
        }
    }
}

void GameManager::AddScore(int points)
{
    if(!mIsGameOver)
    {
        mScore += points;
        SDL_Log("Score: %d", mScore);
        mUIManager->UpdateScore(mScore);
    }
}