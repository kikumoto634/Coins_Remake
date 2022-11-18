#pragma once
#include "3D/BaseObjects.h"
#include "3D/Collider/Collider.h"

class Goal : public BaseObjects, public Collider
{
public:
	~Goal();

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

	//�Փ˔���
	void OnCollision(Collider* TouchCollision) override;

	//Getter
	const Vector3 GetPosition() override {return world.translation;}
	const float GetWidth() override	{return width;}
	const float GetHeight()	override	{return height;}
	const float GetDepth()	override	{return depth;}
	const std::string GetName() override	{return name;}

	//Setter
	void SetVector3(Vector3 position)	{world.translation = position;}
	void SetDepthSp(float Sp)	{DepthSp = Sp;}

private:
	float width = 50;
	float height = 50;
	float depth = 10;
	std::string name = "Goal";

	float DepthSp = 0.f;
};

