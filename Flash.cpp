#include "Flash.h"
#include <Novice.h>

Flash::Flash() { this->Initialize(); }
Flash::~Flash() {}

void Flash::Initialize()
{
	m_color = 0x77770000;		// �F
	m_alpha = 0x0000000;		// �����x
	m_time = 0;					// ���݂̎���
	m_bIsFlash = false;			// �_�Œ���
	m_bIsAlaphUp = true;		// �����x���㏸����
}

void Flash::Update()
{
	// ���ԓ��Ȃ�_�ŏ������s��
	if (m_time > 0)
	{
		m_bIsFlash = true;
		m_time--;

		if (m_bIsAlaphUp)
		{
			// ����
			m_alpha += 0x02;

			// �␳
			if (m_alpha >= 0xFF)
			{
				m_alpha = 0xFF;
				m_bIsAlaphUp = false;
			}

		}
		else
		{
			// ����
			m_alpha -= 0x02;

			// �␳
			if (m_alpha <= 0x00 || m_alpha >= 0xFFFFFFF0)
			{
				m_alpha = 0x00;
				m_bIsAlaphUp = true;
			}

		}

	}
	else
	{
		m_bIsFlash = false;
	}

}
void Flash::Draw() {

	Novice::DrawBox(0, 0, 1280, 720, 0.0f, m_color + m_alpha, kFillModeSolid);

	//Novice::ScreenPrintf(10, 10, "color:%x", m_color);
	//Novice::ScreenPrintf(10, 30, "alpha:%x", m_alpha);
	//Novice::ScreenPrintf(10, 50, "time:%d", m_time);
	//Novice::ScreenPrintf(10, 90, "IsFlashing:%d", m_bIsFlash);
	//Novice::ScreenPrintf(10, 110, "IsAlaphUp:%d", m_bIsAlaphUp);
}


/// <summary>
/// �_�ł�����
/// </summary>
void Flash::ToFlash() {

	if (m_time == 0) {
		m_time = m_kMaxTime;
	}

}

/// <summary>
/// �_�Œ���
/// </summary>
/// <returns>�_�ł��Ă����True��Ԃ�</returns>
bool Flash::GetFlashing() { return m_bIsFlash; }