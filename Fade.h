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
	/// シーン変更できるか
	/// </summary>
	/// <returns></returns>
	bool GetIsOnChange() { return m_bIsOnChange; }
	bool GetIsFadeIn() { return m_bIsFadeIn; }
	bool GetIsFadeOut() { return m_bIsFadeOut; }
	bool GetIsFadeStop() { return m_bIsFadeStop; }
	bool GetIsSceneChange() { return m_bIsSceneChange; }

private:// メンバ変数

	unsigned int m_color = 0xFFFFFF;		// 色
	uint32_t m_alpha = 0x00;				// 透明度
	static const int m_kMaxTime = 256;		// 最大点滅可能時間
	int m_time;								// 現在の時間
	bool m_bIsFadeIn;						// 点灯中か
	bool m_bIsFadeOut;						// 消灯中か
	bool m_bIsFadeStop;						// 点灯・消灯が停止しているか
	bool m_bIsOnChange;						// シーンチェンジを実行できるか
	bool m_bIsSceneChange;					// シーンチェンジ中か

};