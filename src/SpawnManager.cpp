#include "SpawnManager.h"
#include "Core/Game.h"
#include "Player.h"
#include "Enemy.h"
#include "GameManager.h"

SpawnManager::SpawnManager(Game* game) : Actor(game), mCurrentStage(1)
{
    new GameManager(GetGame());
    SpawnPlayer();
    SpawnEnemies(mCurrentStage);    
}

void SpawnManager::UpdateActor(float deltaTime)
{

}

void SpawnManager::SpawnPlayer()
{
    new Player(GetGame());
}

void SpawnManager::SpawnEnemies(int stage)
{
    int numEnemies = 5 + (stage / 2) * 2;

    float enemySpeed = 150.0f + ((stage - 1) /2) * 70.0f;


    for(int i = 0; i < numEnemies; ++i)
    {
        Enemy* enemy = new Enemy(GetGame());
        enemy->SetSpeed(enemySpeed);

        float posX = 150.0f + (i * 70.0f);
        float posY = 100.0f;

        enemy->SetPosition(posX, posY);
    }

}

void SpawnManager::NextStage()
{
    mCurrentStage++;
    SpawnPlayer();
    SpawnEnemies(mCurrentStage);
}

void SpawnManager::Reset()
{
    mCurrentStage = 1;
    SpawnPlayer();
    SpawnEnemies(mCurrentStage);
}