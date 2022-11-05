#pragma once
#include "FbxModelManager.h"
#include "FbxModelObject.h"
#include "WorldTransform.h"
#include "Vector3.h"

#include "Camera.h"
#include "Input.h"

class Player
{
//メンバ関数
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	
	/// <summary>
	/// 更新
	/// </summary>
	void Update(Camera* camera, Input* input);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 後処理
	/// </summary>
	void Finalize();

	//Getter
	Vector3 GetPos()	{return world.translation;}

	//Setter


private:
	/// <summary>
	/// 入力移動
	/// </summary>
	void InputMovement();

//メンバ変数
private:
	//プレイヤー
	FbxModelManager* model;
	FbxModelObject* object;
	WorldTransform world;

	Camera* camera = nullptr;
	Input* input = nullptr;
};

