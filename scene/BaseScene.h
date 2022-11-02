#pragma once
#include "DirectXCommon.h"
#include "Window.h"
#include "Input.h"
#include "Camera.h"

#include "Sprite.h"

#ifdef _DEBUG
#include "SceneStopper.h"
#endif // _DEBUG

class BaseScene
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BaseScene(DirectXCommon* dxCommon, Window* window);

//メンバ関数
public:
	/// <summary>
	/// 起動時
	/// </summary>
	void Application();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 後処理
	/// </summary>
	void Finalize();

//メンバ変数
protected:

#pragma region 汎用機能
	//借りもの
	DirectXCommon* dxCommon = nullptr;
	Window* window = nullptr;
	
	//作成
	Input* input = nullptr;
	Camera* camera = nullptr;
#pragma endregion

	Sprite* sp = nullptr;

#ifdef _DEBUG
	SceneStopper* sceneStopper = nullptr;
#endif // _DEBUG

};

