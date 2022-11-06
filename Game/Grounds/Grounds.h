#pragma once
#include "BaseObjects.h"

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

	//Getter
	Vector3 GetPosition()	{return world.translation;}

	//Setter
	void SetVector3(Vector3 position)	{world.translation = position;}
};

