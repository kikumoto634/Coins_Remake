#pragma once
#include "2D/BaseSprite.h"
#include "Window.h"
#include "Camera.h"

class ScoreSprite : public BaseSprite
{
public:
	~ScoreSprite();

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

	void Finalize() override;

	bool GetIsDead() const {return IsDead;}

	//3D->2D変換
	Vector2 ChangeTransformation(Vector3 targetpos);

private:
	//フェードアウト
	void FadeOut();

	//ベクトル*行列
	Vector3 Vector3Transform( Vector3 &v,  DirectX::XMMATRIX &m);

private:
	Window* window = nullptr;
	Camera* camera = nullptr;

	//消滅時間
	float time = 0.f;
	const float InvisibleTime = 1.0f;

	//色
	float alpha = 1.f;
};

