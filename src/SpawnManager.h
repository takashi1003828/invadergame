#pragma once
#include "Core/Actor.h"

class SpawnManager : public Actor
{
public:
    SpawnManager(class Game* game);
    //更新処理
    void UpdateActor(float deltaTime) override;

    void SpawnPlayer();
    void SpawnEnemies(int stage);

private:
    int mCurrentStage;
};