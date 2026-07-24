#include "SpawnManager.h"
#include "Core/Game.h"
#include "Player.h"
#include "Enemy.h"

SpawnManager::SpawnManager(Game* game) : Actor(game), mCurrentStage(1)
{
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
    int numEnemies = 5 + (stage - 1) * 2;

    for(int i = 0; i < numEnemies; ++i)
    {
        Enemy* enemy = new Enemy(GetGame());

        float posX = 150.0f + (i * 100.0f);
        float posY = 100.0f;


        enemy->SetPosition(posX, posY);
    }

}