#pragma once
#include "Camera.h"

class HitStop
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	bool Update(Camera* camera);

	/// <summary>
	/// �q�b�g�X�g�b�v�J�n
	/// </summary>
	void HitStopStart();

	/// <summary>
	/// ���Z�b�g
	/// </summary>
	void Reset();

	/// <summary>
	/// �t���[���ݒ�
	/// </summary>
	/// <param name="frame">�t���[����</param>
	void SetStopFrame(float frame)	{stopFrame = frame;}

private:
	Camera* camera = nullptr;

	bool IsHitStop = false;

	float stopFrame = 1.f;
	float frame = 0.f;

	//�J�����̉�p
	float cameraViewAngle = 55.f;
};

