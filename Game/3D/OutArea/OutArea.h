#pragma once
#include "3D/BaseObjects.h"
class OutArea : public BaseObjects
{
//ƒƒ“ƒoŠÖ”
public:
	~OutArea();

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

	//Settter
	void SetDepthSp(float Sp)	{DepthSp = Sp;}

private:
	float DepthSp = 0.f;
};

