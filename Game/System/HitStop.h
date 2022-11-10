#pragma once
#include "Camera.h"

class HitStop
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	bool Update(Camera* camera);

	/// <summary>
	/// ヒットストップ開始
	/// </summary>
	void HitStopStart();

	/// <summary>
	/// リセット
	/// </summary>
	void Reset();

	/// <summary>
	/// フレーム設定
	/// </summary>
	/// <param name="frame">フレーム数</param>
	void SetStopFrame(float frame)	{stopFrame = frame;}

private:
	Camera* camera = nullptr;

	bool IsHitStop = false;

	float stopFrame = 1.f;
	float frame = 0.f;

	//カメラの画角
	float cameraViewAngle = 55.f;
};

