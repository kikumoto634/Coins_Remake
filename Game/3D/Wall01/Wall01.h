#pragma once
#include "3D/BaseObjects.h"
#include "3D/Collider/Collider.h"
#include "System/HitStop.h"


class Wall01 : public BaseObjects, public Collider
{
//�����o�֐�
public:
	~Wall01();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(std::string filePath) override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(Camera* camera, HitStop* hitStop);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// �㏈��
	/// </summary>
	void Finalize() override;

	//�Փ˔���
	void OnCollision(Collider* TouchCollision) override;

	//Getter
	const Vector3 GetPosition() override {return world.translation;}

	const float GetWidth() override	{return width;}
	const float GetHeight()	override	{return height;}
	const float GetDepth()	override	{return depth;}
	const std::string GetName() override	{return name;}

	bool GetIsDead() const {return IsDead;}

	//Setter
	void SetVector3(Vector3 position)	{world.translation = position;}
	void SetDepthSp(float Sp)	{DepthSp = Sp;}

//�����o�ϐ�
private:
	float width = 10;
	float height = 10;
	float depth = 10;
	std::string name = "Wall01";

	float DepthSp = 0.f;

	HitStop* hitStop = nullptr;
};

