#pragma once
#include<cstdint>

class Flash
{
public:

	Flash();
	~Flash();
	void Initialize();
	void Update();
	void Draw();


	/// <summary>
	/// 点滅させる
	/// </summary>
	void ToFlash();

	/// <summary>
	/// 点滅中か
	/// </summary>
	/// <returns>点滅していればTrueを返す</returns>
	bool GetFlashing();

	//GetとSetは自分で作ること

private:// メンバ変数

	unsigned int m_color = 0xFFFFFF;		// 色
	uint32_t m_alpha = 0x00;				// 透明度
	static const int m_kMaxTime = 256;		// 最大点滅可能時間
	int m_time;								// 現在の時間
	bool m_bIsFlash;						// 点滅中か
	bool m_bIsAlaphUp;						// 透明度が上昇中か
};