#pragma once
#include "3D/BaseObjects.h"

class Grounds : public BaseObjects
{
//�����o�֐�
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(std::string filePath) override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(Camera* camera);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// �㏈��
	/// </summary>
	void Finalize() override;

	//Settter
	void SetDepthSp(float Sp)	{DepthSp = Sp;}

private:
	float DepthSp = 0.f;
};
