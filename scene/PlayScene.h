#pragma once
#include <list>
#include <sstream>

#include "BaseScene.h"

#include "Sprite.h"
#include "FbxModelManager.h"
#include "FbxModelObject.h"
#include "WorldTransform.h"

#include "3D/Player\Player.h"
#include "3D/Coins/Coins.h"
#include "3D/Grounds/Grounds.h"
#include "3D/OutArea/OutArea.h"
#include "3D/SkyDome/SkyDome.h"
#include "3D/Wall01/Wall01.h"

#include "2D/Score/ScoreSprite.h"

#include "System/HitStop.h"



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
	void CoinPopCommands();
	void CoinPop(Vector3 pos);
	void CoinPopReSet();

	//スコアPOP
	void ScoreUp100Pop();
	void ScoreDown100Pop();

	//地面POP
	void GroundPop(Vector3 position);
	//アウトエリアPOP
	void OutAreaPop(Vector3 position);

	//壁01
	void Wall01Pop(Vector3 position);

private:
	//プレイヤー
	std::unique_ptr<Player> player;

	//コイン
	std::list<std::unique_ptr<Coins>> coin;
	std::stringstream coinPopCommands;
	int waitTime = 0;
	bool IsWait = false;

	//スコア
	std::list<std::unique_ptr<ScoreSprite>> score;

	//地面
	std::list<std::unique_ptr<Grounds>> ground;
	std::list<std::unique_ptr<OutArea>> outArea;

	//天球
	std::unique_ptr<SkyDome> skyDome;

	//壁01
	std::list<std::unique_ptr<Wall01>> wall01;

	//ゲーム進行速度
	float GameSpeed = 0.f;
	const float GameNormalSpeed = 4.f;
	const float GameAcceleratorSpeed = 6.f;

	int frame = 0;
	int second = 0;

	//ヒットストップ
	std::unique_ptr<HitStop> hitStop;
};

