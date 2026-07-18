#include "Core/Game.h"

int main(int argc, char* argv[]){
    Game game;

    //初期化に成功したらループを回す
    if (game.Initialize()){
        game.RunLoop();
    }

    game.Shutdown();

    return 0;
}