#pragma once
#include "3D/BaseObjects.h"
#include "3D/Collider/Collider.h"

class Coins : public BaseObjects, public Collider
{
//ƒƒ“ƒoŠÖ”
public:

	~Coins();

	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize(std::string filePath) override;

	/// <summary>
	/// XV
	/// </summary>
	void Update(Camera* camera);

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw() override;

	/// <summary>
	/// Œãˆ—
	/// </summary>
	void Finalize() override;

	//Õ“Ë”»’è
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
	float width = 15;
	float height = 15;
	float depth = 15;
	std::string name = "Coin";

	float DepthSp = 0.f;
};

