#pragma once
#include "Vector2.h"
#include "Novice.h"
#include "MyMath.h"

enum class Scene {
	Before,
	Stay,
	After
};

class SceneChange {


public:
	void Initialize(const int kWindowWidth, const int kWindowHeight, float stayTimer);
	void Update();
	void Draw();


private:


	/*bool isBefore_ = false;
	bool isStay_ = false;
	bool isAfter_ = false;*/

	Vector2 pos_{ };
	Vector2Int size_{};

	float stayTimer_ = 0;
	float startPos;
	float stayPos;
	float endPos;
	float easingTime = 0.0f;

	Scene scene = Scene::Before;
};