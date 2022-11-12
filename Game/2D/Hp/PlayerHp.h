#pragma once
#include "2D/BaseSprite.h"
#include "Window.h"
#include "Camera.h"

class PlayerHp : public BaseSprite
{
public:
	~PlayerHp();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(UINT textureNumber) override;

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

	//3D->2D変換
	Vector2 ChangeTransformation(Vector3 targetpos);

	/// <summary>
	/// フェード開始
	/// </summary>
	void FadeStart()	{IsFade = true;}

	/// <summary>
	/// 破壊開始
	/// </summary>
	void BreakStart()	{IsBreak = true;}


	void IsInvisibleState(bool IsFlag)	{sprite->SetIsInvisible(IsFlag);}

	//Getter
	bool GetIsDead() const {return IsDead;}

	//Setter
	void SetHpNum(int num)	{HeartNum = num;}

private:
	//フェードアウト
	void FadeOut();

	//破壊
	void HeartBreak();

	//ベクトル*行列
	Vector3 Vector3Transform( Vector3 &v,  DirectX::XMMATRIX &m);

private:
	Window* window = nullptr;
	Camera* camera = nullptr;

	int HeartNum = 1;

	///フェード
	//消滅時間
	bool IsFade = false;
	float Fadetime = 0.f;
	const float FadeInvisibleTime = 1.5f;

	//破壊
	bool IsBreak = false;
	float BreakTime = 0.f;
	const float BreakInvisibleTime = 0.75f;
};

