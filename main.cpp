#include <Novice.h>
#define _USE_MATH_DEFINES
#include "Vector2.h"
#include <math.h>
#include "MyMath.h"
#include "SceneChange.h"

const char kWindowTitle[] = "LE2B_23_マスダリュウ";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	float startPos = 0.0f;
	float endPos = 500.0f;
	float easingTime = 0.0f;
	Vector2 pos{ 0, 500 };
	SceneChange* sceneChange = nullptr;
	sceneChange = new SceneChange();
	sceneChange->Initialize(kWindowWidth, kWindowHeight, 120);


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		sceneChange->Update();
		if (easingTime < 1.0f) {
			easingTime += 1.0f / 60.0f;
		}

		pos.x = MyMath::EaseInF(easingTime, startPos, endPos, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		//
		/// ↓描画処理ここから
		///
		sceneChange->Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
