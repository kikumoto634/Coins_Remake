#pragma once
#include "BaseScene.h"

#include "Sprite.h"
#include "FbxModelManager.h"
#include "FbxModelObject.h"
#include "WorldTransform.h"

#include "Player\Player.h"
#include <Coins/Coins.h>

class PlayScene : public BaseScene
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayScene(DirectXCommon* dxCommon, Window* window);

	/// <summary>
	/// 起動時
	/// </summary>
	void Application() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 後処理
	/// </summary>
	void Finalize() override;

private:
	//プレイヤー
	std::unique_ptr<Player> player;

	//コイン
	std::unique_ptr<Coins> coin;

	//地面
	FbxModelManager* groundModel;
	FbxModelObject* groundObject[10];
	WorldTransform groundWorld[10];

	//カメラ
	Vector3 eye{};
	Vector3 target{};
};

