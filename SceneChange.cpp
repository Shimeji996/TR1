#include "SceneChange.h"

void SceneChange::Initialize(const int kWindowWidth, const int kWindowHeight, float stayTimer) {
	size_.x = kWindowWidth;
	size_.y = kWindowHeight;
	startPos = -size_.x;
	stayPos = 0.0f;
	endPos = size_.x;
	stayTimer_ = stayTimer;
}

void SceneChange::Update() {


	switch (scene)
	{
	case Scene::Before:
		if (easingTime < 1.0f) {
			easingTime += 1.0f / 60.0f;
			if (easingTime >= 1.0f) {
				easingTime = 1.0f;
				scene = Scene::Stay;
			}

			pos_.x = MyMath::EaseInF(easingTime, startPos, stayPos, 1.0f);
			break;
		}

	case Scene::Stay:
		stayTimer_--;

		if (stayTimer_ <= 0.0f) {
			scene = Scene::After;
		}
		easingTime = 0.0f;
		break;

	case Scene::After:
		if (easingTime < 1.0f) {
			easingTime += 1.0f / 60.0f;
			if (easingTime >= 1.0f) {
				easingTime = 1.0f;
			}
		}

		pos_.x = MyMath::EaseInF(easingTime, stayPos, endPos, 1.0f);
		break;

	}
}
void SceneChange::Draw() {

	if (scene == Scene::Stay || scene == Scene::After) {
		Novice::DrawEllipse(640, 360, 16, 16, 0.0f, 0xFFFFFFFF, kFillModeSolid);
	}

	Novice::DrawBox(pos_.x, pos_.y, size_.x, size_.y, 0.0f, BLACK, kFillModeSolid);

	Novice::ScreenPrintf(0, 0, "timer: %f, pos : %f", easingTime, pos_.x);

}