#pragma once
#include <list>
#include <sstream>

#include "BaseScene.h"


#include "Sprite.h"
#include "FbxModelManager.h"
#include "FbxModelObject.h"
#include "WorldTransform.h"

#include "3D/Player/Player.h"
#include "3D/Coins/Coins.h"
#include "3D/Grounds/Grounds.h"
#include "3D/OutArea/OutArea.h"
#include "3D/SkyDome/SkyDome.h"
#include "3D/Wall01/Wall01.h"
#include "3D/Wall02/Wall02.h"
#include "3D/Goal/Goal.h"

#include "2D/Score/ScoreSprite.h"
#include "2D/ScoreText/ScoreText.h"
#include "2D/ScoreBoard/ScoreBoard.h"
#include "2D/ScoreGage/ScoreGage.h"

#include "System/HitStop.h"
#include "Result.h"



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
	//エリアデータ読み込み
	void CSVLoadPopData();
	void PopCommands();

	//コインPOP
	void InitCoinPop();
	void CoinPop(Vector3 pos);

	//地面POP
	void GroundPop(Vector3 position);
	//アウトエリアPOP
	void OutAreaPop(Vector3 position);

	//壁
	void InitWall01Pop();
	void Wall01Pop(Vector3 position);
	void InitWall02Pop();
	void Wall02Pop(Vector3 position, bool IsLRFlag);

	//ゴール
	void InitGoalPop();
	void GoalPop(Vector3 position);

	//スコアPOP
	void ScoreUp100Pop();
	void ScoreDown100Pop();

private:
	//プレイヤー
	std::unique_ptr<Player> player;

	//コイン
	std::list<std::unique_ptr<Coins>> coin;

	//地面
	std::list<std::unique_ptr<Grounds>> ground;
	std::list<std::unique_ptr<OutArea>> outArea;

	//天球
	std::unique_ptr<SkyDome> skyDome;

	//壁
	std::list<std::unique_ptr<Wall01>> wall01;
	std::list<std::unique_ptr<Wall02>> wall02;

	//ゴール
	std::unique_ptr<Goal> goal;

	//スコア
	std::list<std::unique_ptr<ScoreSprite>> score;
	//スコア表
	std::unique_ptr<ScoreText> scoreText;
	//スコアボード
	std::unique_ptr<ScoreBoard> scoreBoard;
	//スコアゲージ
	std::unique_ptr<ScoreGage> scoreGage;

	//リザルト
	std::unique_ptr<Result> result;

	//ゲーム進行速度
	float GameSpeed = 0.f;
	const float GameNormalSpeed = 8.f;
	const float GameAcceleratorSpeed = 15.f;

	int frame = 0;
	int second = 0;

	//ヒットストップ
	std::unique_ptr<HitStop> hitStop;

	//csvコマンド
	std::stringstream popCommands;
	int waitTime = 0;
	bool IsWait = false;
};

