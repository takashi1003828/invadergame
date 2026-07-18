#pragma once
#include "Core/Actor.h"

class Player : public Actor {
public:
    Player(class Game* game);

    //移動処理を書くためオーバーライド
    void UpdateActor(float deltaTime) override;
};