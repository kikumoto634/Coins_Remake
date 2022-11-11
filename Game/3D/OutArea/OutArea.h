#pragma once
#include "3D/BaseObjects.h"
class OutArea : public BaseObjects
{
//�����o�֐�
public:
	~OutArea();

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

