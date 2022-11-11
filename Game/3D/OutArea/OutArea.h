#pragma once
#include "3D/BaseObjects.h"
class OutArea : public BaseObjects
{
//メンバ関数
public:
	~OutArea();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(std::string filePath) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update(Camera* camera);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 後処理
	/// </summary>
	void Finalize() override;

	//Settter
	void SetDepthSp(float Sp)	{DepthSp = Sp;}

private:
	float DepthSp = 0.f;
};

