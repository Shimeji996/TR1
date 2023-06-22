#include "SceneManager.h"
#include <Novice.h>

SceneManager::SceneManager()
{
	this->Initialize();
}

SceneManager::~SceneManager()
{
	delete m_flash;
	delete m_fade;
}

void  SceneManager::Initialize()
{
	m_flash->Initialize();
	m_fade->Initialize();
	m_bIsLoading = false;
}

void SceneManager::Update(char* keys, char* preKeys)
{
	// フラッシュの更新
	m_flash->Update();
	// フェードの更新
	m_fade->Update();

	switch (m_sceneName)
	{
	case SceneName::START:

		// スペースキーを入力したら画面遷移を開始
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			if (!m_fade->GetIsSceneChange()) {
				m_fade->SetSceneChange();
			}
		}

		//	シーンを切り替え
		if (m_fade->GetIsOnChange()) {
			m_fade->SetOnSceneChange();
			m_sceneName = SceneName::END;
		}

		break;
	case SceneName::END:


		break;
	default:
		break;
	}

}

void  SceneManager::Draw()
{
	switch (m_sceneName)
	{
	case SceneName::START:

		break;
	case SceneName::END:

		Novice::DrawEllipse(640, 360, 16, 16, 0.0f, 0xFFFFFFFF, kFillModeSolid);

		break;

	default:
		break;
	}

	// フラッシュの描画
	m_flash->Draw();
	// フェードの描画
	m_fade->Draw();

}