#pragma once
#include "Core/Actor.h"

class GameManager : public Actor
{
public:
    GameManager(class Game* game);

    void UpdateActor(float deltaTime) override;

    void AddScore(int points);

private:
    int mScore;
    bool mIsGameOver;
    class UIManager* mUIManager;
    bool mIsStageCleared;
    int mCurrentStage;
};