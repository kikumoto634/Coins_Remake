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
	void SetDeletePosZ(float z)	{DeletePosZ = z;}
	void SetPopPosZ(float z)	{PopPosZ = z;}
	void SetDepthSp(float Sp)	{DepthSp = Sp;}

private:
	float DeletePosZ = 0.f;
	float PopPosZ = 1200.f;
	float DepthSp = 0.f;
};

