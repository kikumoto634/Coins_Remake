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
	/// 初期化
	/// </summary>
	virtual void Initialize(std::string filePath);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update(Camera* camera);

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// 後処理
	/// </summary>
	virtual void Finalize();

	//Getter
	bool GetIsDead() const {return IsDead;}

	//Setter
	void SetVector3(Vector3 position)	{world.translation = position;}
	void SetRotation(Vector3 rotation)	{world.rotation = rotation;}
	void SetIsDead(bool IsFlag)	{IsDead = IsFlag;}

protected:
	FbxModelManager* model;
	FbxModelObject* object;
	WorldTransform world;

	Camera* camera = nullptr;

	bool IsDead = false;
};

