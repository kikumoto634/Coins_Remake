#pragma once
#include "FbxModelManager.h"
#include "FbxModelObject.h"
#include "WorldTransform.h"
#include "Vector3.h"
#include "Camera.h"

#include <string>

class BaseObjects
{
public:
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	virtual void Initialize(std::string filePath);

	/// <summary>
	/// XV
	/// </summary>
	virtual void Update(Camera* camera);

	/// <summary>
	/// •`‰æ
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// Œãˆ—
	/// </summary>
	virtual void Finalize();

	//Setter
	void SetVector3(Vector3 position)	{world.translation = position;}

protected:
	FbxModelManager* model;
	FbxModelObject* object;
	WorldTransform world;

	Camera* camera = nullptr;

	bool IsDead = false;
};

