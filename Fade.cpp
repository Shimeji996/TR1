#include "Fade.h"
#include <Novice.h>

Fade::Fade() { this->Initialize(); }
Fade::~Fade() {}

void Fade::Initialize()
{
	m_color = 0x00000000;		// 色
	m_alpha = 0x00000000;		// 透明度
	m_time = 60;				// 現在の時間
	m_bIsFadeIn = false;		// 点灯中か
	m_bIsFadeOut = false;		// 消灯中か
	m_bIsFadeStop = false;		// 点灯・消灯が停止しているか
	m_bIsOnChange = false;		// 透明度が上昇中か
	m_bIsSceneChange = false;	// シーンチェンジ中か
}

void Fade::Update()
{
	// シーンチェンジ中
	if (m_bIsSceneChange)
	{
		// フェードイン中
		if (m_bIsFadeIn)
		{
			// 増加
			m_alpha += 0x02;

			// 補正
			if (m_alpha >= 0xFF)
			{
				m_alpha = 0xFF;
				m_bIsFadeIn = false;
				m_bIsFadeStop = true;
			}
		}
		// フェードアウト中
		if (m_bIsFadeOut)
		{
			// 減少
			m_alpha -= 0x02;

			// 補正
			if (m_alpha <= 0x00 || m_alpha >= 0xFFFFFFF9)
			{
				m_alpha = 0x00;
				m_bIsFadeOut = false;
				m_bIsSceneChange = false;
			}
		}
		// フェード停止中
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
