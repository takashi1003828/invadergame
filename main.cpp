#include <SDL2/SDL.h> // 環境によっては <SDL.h> の場合もあります
#include <iostream>

int main(int argc, char* argv[]) {
    // ==========================================
    // 1. 初期化（ここはコピペでOK、暗記不要）
    // ==========================================
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL初期化エラー: " << SDL_GetError() << "\n";
        return -1; // 失敗したら即終了
    }

    // ウィンドウの作成（タイトル、X座標、Y座標、幅、高さ、フラグ）
    SDL_Window* window = SDL_CreateWindow("Invader Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    
    // レンダラー（絵を描くための筆）の作成
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // ループ継続フラグ
    bool isRunning = true;
    SDL_Event event;

    // ==========================================
    // 2. メインループ（ゲームの心臓部）
    // ==========================================
    while (isRunning) {

        // ①【イベント処理】OSからの手紙を受け取る
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false; // ×ボタンが押されたらループを終了
            }
        }

        // ②【更新処理】キャラクターの移動や当たり判定の計算
        // （後々、ここに objectsのUpdate() を書きます）


        // ③【描画処理】画面をクリアして、新しい絵を描く
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 筆の色を「黒」に設定
        SDL_RenderClear(renderer);                      // 画面全体を黒で塗りつぶす

        // （後々、ここに objectsのDraw(renderer) を書きます）

        SDL_RenderPresent(renderer); // 裏で描いた絵を、実際の画面にパッと反映させる
    }

    // ==========================================
    // 3. お片付け（ここもコピペでOK、暗記不要）
    // ==========================================
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}