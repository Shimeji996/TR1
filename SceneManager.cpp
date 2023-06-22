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
	// �t���b�V���̍X�V
	m_flash->Update();
	// �t�F�[�h�̍X�V
	m_fade->Update();

	switch (m_sceneName)
	{
	case SceneName::START:

		// �X�y�[�X�L�[����͂������ʑJ�ڂ��J�n
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			if (!m_fade->GetIsSceneChange()) {
				m_fade->SetSceneChange();
			}
		}

		//	�V�[����؂�ւ�
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

	// �t���b�V���̕`��
	m_flash->Draw();
	// �t�F�[�h�̕`��
	m_fade->Draw();

}