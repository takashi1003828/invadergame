#pragma once
#include <vector>

//前方宣言をする
class Game;
class Component;

class Actor {
public:
    //アクターのステートを定義
    enum State {
        EActive,
        EPaused,
        EDead
    };

    Actor(Game* game);
    virtual ~Actor();

    //更新内容
    void Update(float deltaTime);

    //アクターについているパーツの更新
    void UpdateComponents(float delataTime);

    //アクター独自の更新内容
    virtual void UpdateActor(float deltaTime);

    //パーツをつけるのと消すの
    void AddComponent(Component* component);
    void RemoveComponent(Component* component);

    //ゲッターとセッター
    State GetState() const{return mState;}
    void SetState(State state){ mState = state;}
    Game* GetGame() {return mGame; }

    //座標の取得と設定
    float GetPositionX() const {return mPositionX;}
    float GetPositionY() const {return mPositionY;}
    void SetPosition(float x, float y) {mPositionX = x; mPositionY = y; }

    //スケールの設定と取得
    float GetScale() const { return mScale; }
    void SetScale(float scale) {mScale = scale; }

private:

    //アクターが持つステータス等
    State mState;
    float mPositionX;
    float mPositionY;
    //スケールを設定できるように
    float mScale;

    //このアクターが持つコンポネントの配列
    std::vector<Component*> mComponents;

    //ゲームクラス本体へのポインタ
    Game* mGame;
};