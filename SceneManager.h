#pragma once
#include"Flash.h"
#include"Fade.h"

// ゲームシーンの列挙体
enum class SceneName {
	START,
	END,
};

/// <summary>
/// シーンクラス
/// </summary>
class SceneManager
{
public: // メンバ関数

	SceneManager();
	~SceneManager();

	void Initialize();
	void Update(char* keys, char* preKeys);
	void Draw();

private: // メンバ変数

	// 現在のシーン名
	SceneName m_sceneName = SceneName::START;
	// ロード中か
	bool m_bIsLoading;
	// フラッシュクラス
	Flash* m_flash = new Flash;
	// フェードクラス
	Fade* m_fade = new Fade;

};