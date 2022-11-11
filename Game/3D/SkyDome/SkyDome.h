#pragma once
#include "3D/BaseObjects.h"
class SkyDome : public BaseObjects
{
	//ƒƒ“ƒoŠÖ”
public:
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

	bool GetIsDead() const {return IsDead;}

	//Setter
	void SetVector3(Vector3 position)	{world.translation = position;}
};

