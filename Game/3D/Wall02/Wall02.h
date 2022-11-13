#pragma once
#include "3D/BaseObjects.h"
#include "3D/Collider/Collider.h"
#include "System/HitStop.h"

class Wall02 :public BaseObjects, public Collider
{
//�����o�֐�
public:
	~Wall02();

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

private:
	/// <summary>
	/// �ړ�
	/// </summary>
	void Movement();

//�萔
private:
	const float FallTime = 2.0f;//1s ~ 2s

//�����o�ϐ�
private:
	float width = 10;
	float height = 10;
	float depth = 10;
	std::string name = "Wall01";

	float DepthSp = 0.f;

	float fallTime = 0.f;

	HitStop* hitStop = nullptr;
};

