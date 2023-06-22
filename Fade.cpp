#include "Fade.h"
#include <Novice.h>

Fade::Fade() { this->Initialize(); }
Fade::~Fade() {}

void Fade::Initialize()
{
	m_color = 0x00000000;		// �F
	m_alpha = 0x00000000;		// �����x
	m_time = 60;				// ���݂̎���
	m_bIsFadeIn = false;		// �_������
	m_bIsFadeOut = false;		// ��������
	m_bIsFadeStop = false;		// �_���E��������~���Ă��邩
	m_bIsOnChange = false;		// �����x���㏸����
	m_bIsSceneChange = false;	// �V�[���`�F���W����
}

void Fade::Update()
{
	// �V�[���`�F���W��
	if (m_bIsSceneChange)
	{
		// �t�F�[�h�C����
		if (m_bIsFadeIn)
		{
			// ����
			m_alpha += 0x02;

			// �␳
			if (m_alpha >= 0xFF)
			{
				m_alpha = 0xFF;
				m_bIsFadeIn = false;
				m_bIsFadeStop = true;
			}
		}
		// �t�F�[�h�A�E�g��
		if (m_bIsFadeOut)
		{
			// ����
			m_alpha -= 0x02;

			// �␳
			if (m_alpha <= 0x00 || m_alpha >= 0xFFFFFFF9)
			{
				m_alpha = 0x00;
				m_bIsFadeOut = false;
				m_bIsSceneChange = false;
			}
		}
		// �t�F�[�h��~��
		if (m_bIsFadeStop)
		{
			if (m_time == 60) {
				m_bIsOnChange = true;
			}
			if (m_time > 0) {
				--m_time;
			}
			else if (m_time <= 0 && m_bIsOnChange == false) {
				m_bIsFadeStop = false;
				m_bIsFadeOut = true;
			}
		}
	}

}
void Fade::Draw() {

	Novice::DrawBox(0, 0, 1280, 720, 0.0f, m_color + m_alpha, kFillModeSolid);

	Novice::ScreenPrintf(10, 10, "color:%x", m_color);
	Novice::ScreenPrintf(10, 30, "alpha:%x", m_alpha);
	Novice::ScreenPrintf(10, 50, "time:%d", m_time);
	Novice::ScreenPrintf(10, 90, "IsIn:%d", m_bIsFadeIn);
	Novice::ScreenPrintf(10, 110, "IsOut:%d", m_bIsFadeOut);
	Novice::ScreenPrintf(10, 130, "IsStop:%d", m_bIsFadeStop);
	Novice::ScreenPrintf(10, 150, "IsSceneChange:%d", m_bIsSceneChange);
}
