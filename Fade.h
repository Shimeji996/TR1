#pragma once
#include<cstdint>

class Fade
{
public:

	Fade();
	~Fade();
	void Initialize();
	void Update();
	void Draw();

	void SetSceneChange() { m_bIsSceneChange = true; m_bIsFadeIn = true; m_time = 60; }
	void SetOnSceneChange() { m_bIsOnChange = false; }

	/// <summary>
	/// �V�[���ύX�ł��邩
	/// </summary>
	/// <returns></returns>
	bool GetIsOnChange() { return m_bIsOnChange; }
	bool GetIsFadeIn() { return m_bIsFadeIn; }
	bool GetIsFadeOut() { return m_bIsFadeOut; }
	bool GetIsFadeStop() { return m_bIsFadeStop; }
	bool GetIsSceneChange() { return m_bIsSceneChange; }

private:// �����o�ϐ�

	unsigned int m_color = 0xFFFFFF;		// �F
	uint32_t m_alpha = 0x00;				// �����x
	static const int m_kMaxTime = 256;		// �ő�_�ŉ\����
	int m_time;								// ���݂̎���
	bool m_bIsFadeIn;						// �_������
	bool m_bIsFadeOut;						// ��������
	bool m_bIsFadeStop;						// �_���E��������~���Ă��邩
	bool m_bIsOnChange;						// �V�[���`�F���W�����s�ł��邩
	bool m_bIsSceneChange;					// �V�[���`�F���W����

};