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
	/// �_�ł�����
	/// </summary>
	void ToFlash();

	/// <summary>
	/// �_�Œ���
	/// </summary>
	/// <returns>�_�ł��Ă����True��Ԃ�</returns>
	bool GetFlashing();

	//Get��Set�͎����ō�邱��

private:// �����o�ϐ�

	unsigned int m_color = 0xFFFFFF;		// �F
	uint32_t m_alpha = 0x00;				// �����x
	static const int m_kMaxTime = 256;		// �ő�_�ŉ\����
	int m_time;								// ���݂̎���
	bool m_bIsFlash;						// �_�Œ���
	bool m_bIsAlaphUp;						// �����x���㏸����
};