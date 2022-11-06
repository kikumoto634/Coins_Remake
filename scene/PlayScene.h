#pragma once
#include <list>
#include <sstream>

#include "BaseScene.h"

#include "Sprite.h"
#include "FbxModelManager.h"
#include "FbxModelObject.h"
#include "WorldTransform.h"

#include "Player\Player.h"
#include "Coins/Coins.h"
#include "Grounds/Grounds.h"



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
	//コインPOP
	void LoadCoinPopData();
	void UpdateCoinPopCommands();
	void CoinPop(Vector3 pos);


	void GroundPop(Vector3 position);


private:
	//プレイヤー
	std::unique_ptr<Player> player;

	//コイン
	std::list<std::unique_ptr<Coins>> coin;
	std::stringstream coinPopCommands;
	int waitTime = 0;
	bool IsWait = false;

	//地面
	std::list<std::unique_ptr<Grounds>> ground;

	int frame = 0;
};

