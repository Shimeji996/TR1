#include "Flash.h"
#include <Novice.h>

Flash::Flash() { this->Initialize(); }
Flash::~Flash() {}

void Flash::Initialize()
{
	m_color = 0x77770000;		// 色
	m_alpha = 0x0000000;		// 透明度
	m_time = 0;					// 現在の時間
	m_bIsFlash = false;			// 点滅中か
	m_bIsAlaphUp = true;		// 透明度が上昇中か
}

void Flash::Update()
{
	// 時間内なら点滅処理を行う
	if (m_time > 0)
	{
		m_bIsFlash = true;
		m_time--;

		if (m_bIsAlaphUp)
		{
			// 増加
			m_alpha += 0x02;

			// 補正
			if (m_alpha >= 0xFF)
			{
				m_alpha = 0xFF;
				m_bIsAlaphUp = false;
			}

		}
		else
		{
			// 減少
			m_alpha -= 0x02;

			// 補正
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
/// 点滅させる
/// </summary>
void Flash::ToFlash() {

	if (m_time == 0) {
		m_time = m_kMaxTime;
	}

}

/// <summary>
/// 点滅中か
/// </summary>
/// <returns>点滅していればTrueを返す</returns>
bool Flash::GetFlashing() { return m_bIsFlash; }