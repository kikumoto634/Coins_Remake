#pragma once
#include "FbxModelManager.h"
#include "FbxModelObject.h"
#include "WorldTransform.h"
#include "Vector3.h"
#include "Camera.h"

#include <string>

class BaseObjects
{
protected:
	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize(std::string filePath);

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update(Camera* camera);

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// �㏈��
	/// </summary>
	virtual void Finalize();

protected:
	FbxModelManager* model;
	FbxModelObject* object;
	WorldTransform world;

	Camera* camera = nullptr;
};

