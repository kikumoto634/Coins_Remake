#pragma once
#include "Vector3.h"

#include <DirectXMath.h>

class ViewProjection
{
public:
	using XMMATRIX = DirectX::XMMATRIX;

public:
	void UpdateViewMatrix();
	void UpdateProjectionMatrix(int width, int height);

public:
	//�J�������
	//�������e
	XMMATRIX matProjection;	//�v���W�F�N�V�����s��
	//�r���[�ϊ��s��
	XMMATRIX matView;		//�r���[�s��
	Vector3 eye;			//���_���W
	Vector3 target;		//�����_���W
	Vector3 up;			//������x�N�g��

	//�㉺��p
	float angle;

	XMMATRIX matViewProjection;
};

