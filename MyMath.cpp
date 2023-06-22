#include "MyMath.h"

#pragma region 線形補間関数

/// <summary>
/// 線形補間関数(EaseIn)(float)
/// </summary>
/// <param name="t">現在のt</param>
/// <param name="start">開始値</param>
/// <param name="end">終了値</param>
/// <param name="time">かかる秒数</param>
/// <returns>イージングされた値(float)</returns>
float MyMath::EaseInF(float t, float start, float end, float time) {
	float easeT = t * t;
	return (1.0f - easeT / time) * start + easeT / time * end;
}

