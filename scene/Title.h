#pragma once
#include "BaseScene.h"

#include "3D/Player/Player.h"
#include "3D/Grounds/Grounds.h"
#include "3D/OutArea/OutArea.h"
#include "3D/SkyDome/SkyDome.h"

class Title : public BaseScene
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Title(DirectXCommon* dxCommon, Window* window);

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
	//地面POP
	void GroundPop(Vector3 position);
	//アウトエリアPOP
	void OutAreaPop(Vector3 position);

private:
	float GameSpeed = 6.f;

	//プレイヤー
	std::unique_ptr<Player> playerObj;

	//天球
	std::unique_ptr<SkyDome> skyDome;

	//地面
	std::list<std::unique_ptr<Grounds>> ground;
	std::list<std::unique_ptr<OutArea>> outArea;

	//タイトルロゴ
	std::unique_ptr<BaseSprite> titleLogo;

#ifdef _DEBUG
	Vector3 target;
	Vector3 eye;
#endif // _DEBUG

};

