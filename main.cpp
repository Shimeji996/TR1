#include <Novice.h>
#define _USE_MATH_DEFIENS
#include <cmath>
#include <assert.h>
#include <Matrix4x4.h>
#include "Vector3.h"
#include <ImGuiManager.h>

const char kWindowTitle[] = "LE2B_23_マスダリュウ";

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			result.m[y][x] = 0;
			for (int k = 0; k < 4; k++)
			{
				result.m[y][x] += m1.m[y][k] * m2.m[k][x];
			}
		}
	}
	return result;
};
Matrix4x4 MakeTranslateMatrix(const Vector3& translate)
{
	Matrix4x4 result;

	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;

	return result;
};
Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 result;

	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
};

Matrix4x4 MakeRotateXMatrix(float radian)
{
	Matrix4x4 result;

	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = cosf(radian);
	result.m[1][2] = sinf(radian);
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = -sinf(radian);
	result.m[2][2] = cosf(radian);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
};

Matrix4x4 MakeRotateYMatrix(float radian)
{
	Matrix4x4 result;

	result.m[0][0] = cosf(radian);
	result.m[0][1] = 0.0f;
	result.m[0][2] = -sinf(radian);
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0.0f;

	result.m[2][0] = sinf(radian);
	result.m[2][1] = 0.0f;
	result.m[2][2] = cosf(radian);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
};

Matrix4x4 MakeRotateZMatrix(float radian)
{
	Matrix4x4 result;

	result.m[0][0] = cosf(radian);
	result.m[0][1] = sinf(radian);
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = -sinf(radian);
	result.m[1][1] = cosf(radian);
	result.m[1][2] = 0;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
};

Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate)
{

	Matrix4x4 result{};

	Matrix4x4 tempXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 tempYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 tempZMatrix = MakeRotateZMatrix(rotate.z);

	result = Multiply(tempXMatrix, Multiply(tempYMatrix, tempZMatrix));

	return result;

}

Matrix4x4 Inverse(const Matrix4x4& m)
{
	Matrix4x4 result;
	float determinant = m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]
		+ m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]
		+ m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]
		- m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]
		- m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]
		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]
		- m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]
		- m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]
		+ m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]
		+ m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]
		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]
		+ m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]
		- m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]
		- m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]
		- m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]
		+ m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]
		+ m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];
	if (determinant < 0)
	{
		determinant *= -1;
	}

	result.m[0][0] = 1 / determinant * (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][2] + m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[1][3] * m.m[2][2] * m.m[3][2] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]);

	result.m[0][1] = 1 / determinant * (-(m.m[0][1] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[2][3] * m.m[3][2]) - (m.m[0][3] * m.m[2][1] * m.m[3][2])
		+ m.m[0][3] * m.m[2][2] * m.m[3][2] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]);

	result.m[0][2] = 1 / determinant * (m.m[1][1] * m.m[1][2] * m.m[3][3] + m.m[1][2] * m.m[1][3] * m.m[3][2] + m.m[1][3] * m.m[1][1] * m.m[3][2]
		- m.m[1][3] * m.m[1][2] * m.m[3][2] - m.m[1][2] * m.m[1][1] * m.m[3][3] - m.m[1][1] * m.m[1][3] * m.m[3][2]);

	result.m[0][3] = 1 / determinant * (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][2] + m.m[0][3] * m.m[1][1] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[3][2] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]);

	result.m[1][0] = 1 / determinant * (-(m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[1][2] * m.m[2][3] * m.m[3][2]) - (m.m[1][3] * m.m[2][1] * m.m[3][2])
		+ m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][2]);

	result.m[1][1] = 1 / determinant * (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][2] + m.m[0][3] * m.m[2][1] * m.m[3][2]
		- m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][2]);

	result.m[1][2] = 1 / determinant * (-(m.m[0][1] * m.m[1][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][3] * m.m[3][0]) - (m.m[0][3] * m.m[1][0] * m.m[3][2])
		+ m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]);

	result.m[1][3] = 1 / determinant * (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][2]);

	result.m[2][0] = 1 / determinant * (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1]
		- m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]);

	result.m[2][1] = 1 / determinant * (-(m.m[0][0] * m.m[2][1] * m.m[3][3]) - (m.m[0][1] * m.m[2][3] * m.m[3][0]) - (m.m[0][3] * m.m[2][0] * m.m[3][1])
		+ m.m[0][3] * m.m[2][1] * m.m[3][0] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]);

	result.m[2][2] = 1 / determinant * (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1]
		- m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]);

	result.m[2][3] = 1 / determinant * (-(m.m[0][0] * m.m[1][1] * m.m[2][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0]) - (m.m[0][3] * m.m[1][0] * m.m[2][1])
		+ m.m[0][3] * m.m[1][1] * m.m[2][1] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]);

	result.m[3][0] = 1 / determinant * (-(m.m[1][0] * m.m[2][1] * m.m[3][2] - (m.m[1][1] * m.m[2][2] * m.m[3][0])) - (m.m[1][2] * m.m[2][0] * m.m[3][1])
		+ m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]);

	result.m[3][1] = 1 / determinant * (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]);

	result.m[3][2] = 1 / determinant * (-(m.m[0][0] * m.m[1][1] * m.m[3][2]) - (m.m[0][1] * m.m[1][2] * m.m[3][0]) - (m.m[0][2] * m.m[1][0] * m.m[3][1])
		+ m.m[0][2] * m.m[1][1] * m.m[3][0] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][2] * m.m[1][0] * m.m[3][1]);

	result.m[3][3] = 1 / determinant * (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][0] * m.m[2][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]);

	return result;

};

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

	Matrix4x4 result;

	Matrix4x4 Scale = MakeScaleMatrix(scale);
	Matrix4x4 Rotate = MakeRotateXYZMatrix(rotate);
	Matrix4x4 Translate = MakeTranslateMatrix(translate);

	result.m[0][0] = Scale.m[0][0] * Rotate.m[0][0];
	result.m[0][1] = Scale.m[0][0] * Rotate.m[0][1];
	result.m[0][2] = Scale.m[0][0] * Rotate.m[0][2];
	result.m[0][3] = 0.0f;

	result.m[1][0] = Scale.m[1][1] * Rotate.m[1][0];
	result.m[1][1] = Scale.m[1][1] * Rotate.m[1][1];
	result.m[1][2] = Scale.m[1][1] * Rotate.m[1][2];
	result.m[1][3] = 0.0f;

	result.m[2][0] = Scale.m[2][2] * Rotate.m[2][0];
	result.m[2][1] = Scale.m[2][2] * Rotate.m[2][1];
	result.m[2][2] = Scale.m[2][2] * Rotate.m[2][2];
	result.m[2][3] = 0.0f;

	result.m[3][0] = Translate.m[3][0];
	result.m[3][1] = Translate.m[3][1];
	result.m[3][2] = Translate.m[3][2];
	result.m[3][3] = 1.0f;

	return result;

}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 result;

	result.m[0][0] = (1 / aspectRatio) * (1 / tanf(fovY / 2));
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 1 / tanf(fovY / 2);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1;

	result.m[3][0] = 1;
	result.m[3][1] = 1;
	result.m[3][2] = -nearClip * farClip / (farClip - nearClip);
	result.m[3][3] = 0;

	return result;
}

Matrix4x4 MakeViewportMatrix(float left, float top, float widte, float height, float minDepth, float maxDepth)
{
	Matrix4x4 result;

	result.m[0][0] = widte / 2;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = -height / 2;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = maxDepth - minDepth;
	result.m[2][3] = 0;

	result.m[3][0] = left + widte / 2;
	result.m[3][1] = top + height / 2;
	result.m[3][2] = minDepth;
	result.m[3][3] = 1;

	return result;
}
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix)
{
	Vector3 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];

	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
};

unsigned int GetColor(int red, int green, int blue, int alpha) {
	unsigned int hex = 0x00000000;
	red = red << 24;
	green = green << 16;
	blue = blue << 8;
	alpha = alpha << 0;
	return hex = red + green + blue + alpha;
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	int textureH = Novice::LoadTexture("white1x1.png");
	Vector3 rotate = {};
	Vector3 translate = {};

	Vector3 cameraPosition = { 0,0,-1000 };

#pragma region 矩形A

	Vector3 kLocalVertices[4]{};
	Vector3 kLocalStartVertices[4]{};
	Vector3 kLocalEndVertices[4]{};

	// 矩形の4点座標
	kLocalVertices[0] = { 640, 360, 0 };
	kLocalVertices[1] = { 1280, 360, 0 };
	kLocalVertices[2] = { 640, -360, 0 };
	kLocalVertices[3] = { 1280, -360, 0 };

	// 線形補間の始点
	kLocalStartVertices[0] = { 0, 360, 0 };
	kLocalStartVertices[1] = { 640, 360, 0 };
	kLocalStartVertices[2] = { 0, -360, 0 };
	kLocalStartVertices[3] = { 640, -360, 0 };

	// 線形補完の終点
	kLocalEndVertices[0] = { 640, 360, 0 };
	kLocalEndVertices[1] = { 1280, 360, 0 };
	kLocalEndVertices[2] = { 640, -360, 0 };
	kLocalEndVertices[3] = { 1280, -360, 0 };

#pragma endregion

#pragma region 矩形B

	Vector3 kLocalVerticesReverse[4]{};
	Vector3 kLocalStartVerticesReverse[4]{};
	Vector3 kLocalEndVerticesReverse[4]{};

	// 矩形の4点座標
	kLocalVerticesReverse[0] = { -1280, 360, 0 };
	kLocalVerticesReverse[1] = { -640, 360, 0 };
	kLocalVerticesReverse[2] = { -1280, -360, 0 };
	kLocalVerticesReverse[3] = { -640, -360, 0 };

	// 線形補間の始点
	kLocalStartVerticesReverse[0] = { -640, 360, 0 };
	kLocalStartVerticesReverse[1] = { 0, 360, 0 };
	kLocalStartVerticesReverse[2] = { -640, -360, 0 };
	kLocalStartVerticesReverse[3] = { 0, -360, 0 };

	// 線形補完の終点
	kLocalEndVerticesReverse[0] = { -1280, 360, 0 };
	kLocalEndVerticesReverse[1] = { -640, 360, 0 };
	kLocalEndVerticesReverse[2] = { -1280, -360, 0 };
	kLocalEndVerticesReverse[3] = { -640, -360, 0 };

#pragma endregion

	// 線形補完の値
	const float min = 0.0f;
	const float max = 1.0f;
	float t = 0;
	float easedT = 0;

	// 線形補完のフラグ
	bool isClose = 0;
	bool isOpen = 0;

	int CloseTimer = 0;

	int red = 0xFF;
	int green = 0x00;
	int blue = 0x00;
	int alpha = 0xFF;
	unsigned color = GetColor(red, green, blue, alpha);


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

		if (!isClose && !isOpen) {
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				isClose = 1;
			}
		}

		if (isClose == 1) {

			// 数値を増加
			t += 0.01f;

			// ｔの値が最大値以上であれば線形補完を停止
			if (t >= max) {
				t = max;
				CloseTimer += 1;
				if (CloseTimer == 120) {
					isClose = false;
					isOpen = true;
				}
			}

			// イージングを行う
			easedT = t * t;

			// ｔの値に応じて座標を移動させる
			for (uint32_t i = 0; i < 4; i++) {
				kLocalVertices[i].x = (1.0f - easedT) * kLocalEndVertices[i].x + easedT * kLocalStartVertices[i].x;
				kLocalVertices[i].y = (1.0f - easedT) * kLocalEndVertices[i].y + easedT * kLocalStartVertices[i].y;
			}

			// ｔの値に応じて座標を移動させる
			for (uint32_t i = 0; i < 4; i++) {
				kLocalVerticesReverse[i].x = (1.0f - easedT) * kLocalEndVerticesReverse[i].x + easedT * kLocalStartVerticesReverse[i].x;
				kLocalVerticesReverse[i].y = (1.0f - easedT) * kLocalEndVerticesReverse[i].y + easedT * kLocalStartVerticesReverse[i].y;
			}


		}


		if (isOpen == 1) {

			// 数値を増加
			t -= 0.01f;

			// ｔの値が最大値以上であれば線形補完を停止
			if (t <= min) {
				t = min;
				isOpen = false;
			}

			// イージングを行う
			easedT = t * t;

			// ｔの値に応じて座標を移動させる
			for (uint32_t i = 0; i < 4; i++) {
				kLocalVertices[i].x = (1.0f - easedT) * kLocalEndVertices[i].x + easedT * kLocalStartVertices[i].x;
				kLocalVertices[i].y = (1.0f - easedT) * kLocalEndVertices[i].y + easedT * kLocalStartVertices[i].y;
			}

			// ｔの値に応じて座標を移動させる
			for (uint32_t i = 0; i < 4; i++) {
				kLocalVerticesReverse[i].x = (1.0f - easedT) * kLocalEndVerticesReverse[i].x + easedT * kLocalStartVerticesReverse[i].x;
				kLocalVerticesReverse[i].y = (1.0f - easedT) * kLocalEndVerticesReverse[i].y + easedT * kLocalStartVerticesReverse[i].y;
			}

		}


		Matrix4x4 cameraMatrix =
			MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);

		Matrix4x4 viewMatrix = Inverse(cameraMatrix);

		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);

		Matrix4x4 projectionMatrix =
			MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);

		Matrix4x4 worldViewPrjectionMatrix =
			Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));

		Matrix4x4 viewportMatrix =
			MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		Vector3 screenVerices[4];
		for (uint32_t i = 0; i < 4; ++i)
		{
			Vector3 ndcVertex = Transform(kLocalVertices[i], worldViewPrjectionMatrix);
			screenVerices[i] = Transform(ndcVertex, viewportMatrix);
		}

		Vector3 screenVericesReverse[4];
		for (uint32_t i = 0; i < 4; ++i)
		{
			Vector3 ndcVertex = Transform(kLocalVerticesReverse[i], worldViewPrjectionMatrix);
			screenVericesReverse[i] = Transform(ndcVertex, viewportMatrix);
		}

		color = GetColor(red, green, blue, alpha);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		if (CloseTimer == 120) {
			Novice::DrawEllipse(640, 360, 16, 16, 0.0f, 0xFFFFFFFF, kFillModeSolid);
		}

		Novice::DrawQuad(
			int(screenVerices[0].x), int(screenVerices[0].y),
			int(screenVerices[1].x), int(screenVerices[1].y),
			int(screenVerices[2].x), int(screenVerices[2].y),
			int(screenVerices[3].x), int(screenVerices[3].y),
			0, 0,
			1, 1,
			textureH, color
		);

		Novice::DrawQuad(
			int(screenVericesReverse[0].x), int(screenVericesReverse[0].y),
			int(screenVericesReverse[1].x), int(screenVericesReverse[1].y),
			int(screenVericesReverse[2].x), int(screenVericesReverse[2].y),
			int(screenVericesReverse[3].x), int(screenVericesReverse[3].y),
			0, 0,
			1, 1,
			textureH, color
		);

		Novice::ScreenPrintf(0, 0, "%d", CloseTimer);

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
