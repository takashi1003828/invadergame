#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>

class Actor;
class SpriteComponent;

class Game{
public:
    //コンストラクタ・デストラクタ
    Game();
    ~Game();

    //ゲームの初期化やメインループ、終了処理
    bool Initialize();
    void RunLoop();
    void Shutdown();

    //アクターの追加と削除
    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);

    //スプライトの追加と削除
    void AddSprite(SpriteComponent* sprite);
    void RemoveSprite(SpriteComponent* sprite);

    //Textureを持ってくるための関数
    SDL_Texture* GetTexture(const std::string& fileName);

    //アクターのリストを取得する
    const std::vector<Actor*>& GetActors() const {return mActors; }

private:

    //ゲームループを構成する3つの主要ステップ
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    
    //ウィンドウとレンダラーの変数
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    //ループフラグ
    bool mIsRunning;

    //現在のアクターを格納する配列
    std::vector<Actor*> mActors;
    //アップデートで作成されたアクター格納配列
    std::vector<Actor*> mPendingActors;

    //スプライトを格納する配列
    std::vector<SpriteComponent*> mSprites;

    //mActorにmPending..が追加できるかの判別フラグ
    bool mUpdatingActors;

    //時間をカウント
    Uint32 mTicksCount;
};