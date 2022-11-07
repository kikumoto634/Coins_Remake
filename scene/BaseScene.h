#pragma once
#include "DirectXCommon.h"
#include "Window.h"
#include "Input.h"
#include "Camera.h"

#include "Sprite.h"

#include "Collider/CollisionManager.h"

#ifdef _DEBUG
#include "SceneStopper.h"
#include "DebugText.h"
#endif // _DEBUG

class BaseScene
{
//メンバ関数
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BaseScene(DirectXCommon* dxCommon, Window* window);

	/// <summary>
	/// 起動時
	/// </summary>
	virtual void Application();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 後更新
	/// </summary>
	void EndUpdate();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// 後描画
	/// </summary>
	void EndDraw();

	/// <summary>
	/// 後処理
	/// </summary>
	virtual void Finalize();

	//衝突判定と応答
	void CheckAllCollision();
private:
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
	bool CheckCollisionDetail(Collider* colliderA, Collider* colliderB);

//メンバ変数
protected:

#pragma region 汎用機能
	//借りもの
	DirectXCommon* dxCommon = nullptr;
	Window* window = nullptr;
	
	//作成
	Input* input = nullptr;
	Camera* camera = nullptr;
	std::unique_ptr<DebugText> debugText;

	//衝突判定
	std::unique_ptr<CollisionManager> collisionManager;

#pragma endregion

#ifdef _DEBUG
	SceneStopper* sceneStopper = nullptr;
#endif // _DEBUG

};

