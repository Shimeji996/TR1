#pragma once
#include"Flash.h"
#include"Fade.h"

// �Q�[���V�[���̗񋓑�
enum class SceneName {
	START,
	END,
};

/// <summary>
/// �V�[���N���X
/// </summary>
class SceneManager
{
public: // �����o�֐�

	SceneManager();
	~SceneManager();

	void Initialize();
	void Update(char* keys, char* preKeys);
	void Draw();

private: // �����o�ϐ�

	// ���݂̃V�[����
	SceneName m_sceneName = SceneName::START;
	// ���[�h����
	bool m_bIsLoading;
	// �t���b�V���N���X
	Flash* m_flash = new Flash;
	// �t�F�[�h�N���X
	Fade* m_fade = new Fade;

};