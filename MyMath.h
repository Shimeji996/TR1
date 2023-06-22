#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <ctime>
#include <cassert>
#include "Vector2.h"
//nclude "MyStruct.h"
//nclude "MyEnum.h"

struct Matrix3x3 {
	float m[3][3];
};

enum EasingType {
	TypeEaseNormal,
	TypeEaseIn,
	TypeEaseOut
};

/// <summary>
/// 二次元座標系の計算クラス
/// </summary>
class MyMath
{
public:

#pragma region 線形補間関数

	/// <summary>
	/// 線形補間関数(EaseIn)(float)
	/// </summary>
	/// <param name="t">現在のt</param>
	/// <param name="start">開始値</param>
	/// <param name="end">終了値</param>
	/// <param name="time">かかる秒数</param>
	/// <returns>イージングされた値(float)</returns>
	static float EaseInF(float t, float start, float end, float time);

};