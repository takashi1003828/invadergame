#include "Core/Game.h"
#include "Core/Actor.h"
#include "Core/SpriteComponent.h"
#include "SpawnManager.h"
#include <SDL2/SDL_image.h>

//コンストラクタ
//mのつくローカルな変数の初期化
Game::Game() : mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mUpdatingActors(false), mTicksCount(0) {

}

Game::~Game() {

}

//ゲームの初期化
bool Game::Initialize(){
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        return false;
    }

    //ウィンドウの作成
    mWindow = SDL_CreateWindow("Invaders",100, 100, 800, 600, 0);
    if(!mWindow){
        return false;
    }

    //レンダラーの作成
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!mRenderer){
        return false;
    }

    SDL_StopTextInput();

    //時間取得
    mTicksCount = SDL_GetTicks();

    new SpawnManager(this);

    return true;
}


//ゲームの核となるループ
void Game::RunLoop(){
    while(mIsRunning){
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

//入力を受け付ける場所
void Game::ProcessInput(){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }
    }

    //キーボードの入力状態からEscで終了
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]){
        mIsRunning = false;
    }
}

//ゲームの計算をする処理
void Game::UpdateGame(){

    while(!SDL_TICKS_PASSED(SDL_GetTicks(),mTicksCount + 16));

    //デルタタイム計算最大値を0.05に
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f){
        deltaTime = 0.05f;
    }
    mTicksCount = SDL_GetTicks();

    //全アクターの更新
    //アクターを更新する：true
    mUpdatingActors = true;
    //配列内のすべてのアクターを更新する
    for(auto actor : mActors){
        actor->Update(deltaTime);
    }
    //アクター更新終了
    mUpdatingActors = false;

    //更新中に追加されたアクターをメインの配列に移動
    //Pendingをアクターに追加する
    for(auto pending : mPendingActors){
        mActors.emplace_back(pending);
    }
    //仮のアクター置き場を削除
    mPendingActors.clear();

    //死んだアクターを配列から削除
    std::vector<Actor*> deadActors;
    for (auto actor : mActors){
        if (actor->GetState() == Actor::EDead){
            deadActors.emplace_back(actor);
        }
    }

    //メモリから削除
    for(auto actor : deadActors){
        delete actor;
    }
}

//描画を出力する
void Game::GenerateOutput(){
    //背景を一旦描画
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    //スプライトの描画
    for (auto sprite : mSprites){
        sprite->Draw(mRenderer);
    }
    //バックバッファとフロントバッファを入れ替えて画面更新
    SDL_RenderPresent(mRenderer);
}

//ゲームシャットダウン時の処理
void Game::Shutdown(){
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

//アクターを配列に追加するための関数
void Game::AddActor(Actor* actor){
    if(mUpdatingActors){
        mPendingActors.emplace_back(actor);
    } else{
        mActors.emplace_back(actor);
    }
}

//アクターの配列から削除する関数
void Game::RemoveActor(Actor* actor){
    //消したいアクターをまずはPendingから探す
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(),actor);
    //もし見つかったら削除
    if (iter != mPendingActors.end()){
        std::vector<Actor*>::iterator tempIter = iter;
        mPendingActors.erase(tempIter);
    }

    //メインの配列の中にあるか探して消す
    iter = std::find(mActors.begin(),mActors.end(), actor);
    //もし見つかったら削除
    if(iter != mActors.end()){
        std::vector<Actor*>::iterator tempIter = iter;
        mActors.erase(tempIter);
    }
}

//スプライトを追加
void Game::AddSprite(SpriteComponent* sprite){
    int myDrawOrder = sprite->GetDrawOrder();
    auto iter = mSprites.begin();
    for(; iter != mSprites.end(); ++iter){
        if(myDrawOrder < (*iter)->GetDrawOrder()){
            break;
        }
    }
    mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite){
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    if (iter != mSprites.end()) {
        mSprites.erase(iter);
    }
}

SDL_Texture* Game::GetTexture(const std::string& fileName){
    //BMP画像を読み込む
    SDL_Surface* surf = IMG_Load(fileName.c_str());
    if(!surf){
        SDL_Log("画像の読み取り失敗：%s,理由：%s",fileName.c_str(), SDL_GetError());
        return nullptr;
    }
    //表面データsurfaceから描画ようのテクスチャを作成
    SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surf);
    SDL_FreeSurface(surf);
    return tex;
}