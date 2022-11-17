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
	/// èâä˙âª
	/// </summary>
	virtual void Initialize(std::string filePath);

	/// <summary>
	/// çXêV
	/// </summary>
	virtual void Update(Camera* camera);

	/// <summary>
	/// ï`âÊ
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// å„èàóù
	/// </summary>
	virtual void Finalize();

	//Setter
	void SetVector3(Vector3 position)	{world.translation = position;}
	void SetRotation(Vector3 rotation)	{world.rotation = rotation;}

protected:
	FbxModelManager* model;
	FbxModelObject* object;
	WorldTransform world;

	Camera* camera = nullptr;

	bool IsDead = false;
};

