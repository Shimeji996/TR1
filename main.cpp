#include <Novice.h>
#define _USE_MATH_DEFINES
#include "Vector2.h"
#include <math.h>


const char kWindowTitle[] = "LE2B_23_マスダリュウ";

struct Ease {
	float t;
	Vector2 startPos;
	Vector2 endPos;
	bool isMove;
};

struct Object {
	Vector2 pos;

	int coolTime;
};

void easeInOutElasticMoveX(Ease& ease, Object& object) {
	if (ease.t >= 0.99f) {
		ease.isMove = false;
	}
	if (ease.isMove) {
		ease.t += 0.01f;

		const float c5 = (2.0f * M_PI) / 4.5f;

		float easeT = ease.t == 0.0f
			? 0.0f
			: ease.t == 1.0f
			? 1.0f
			: ease.t < 0.5f
			? -(powf(2.0f, 20.0f * ease.t - 10.0f) * sinf((20.0f * ease.t - 11.125f) * c5)) / 2.0f
			: (powf(2.0f, -20.0f * ease.t + 10.0f) * sinf((20.0f * ease.t - 11.125f) * c5)) / 2.0f + 1.0f;

		object.pos.y = (1.0f - easeT) * ease.startPos.y + easeT * ease.endPos.y;
	}
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//イージング　ここから
	Ease ease{
		0,
		{0,-1280},
		{0,0 },
		true,
	};

	Object title{
		{0,-1280},
		0,
	};
	//イージング　ここまで


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

		easeInOutElasticMoveX(ease, title);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawBox(title.pos.x, title.pos.y, 1280, 720, 0.0f, BLACK, kFillModeSolid);

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
