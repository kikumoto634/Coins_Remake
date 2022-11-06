#pragma once
#include "BaseObjects.h"

class Grounds : public BaseObjects
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

	//Getter
	Vector3 GetPosition()	{return world.translation;}

	//Setter
	void SetVector3(Vector3 position)	{world.translation = position;}
};

