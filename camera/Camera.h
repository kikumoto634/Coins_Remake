#pragma once
#include "Window.h"
#include "Vector3.h"

#include "ViewProjection.h"

#include <DirectXMath.h>

/// <summary>
/// カメラ
/// </summary>
class Camera
{
public:
	using XMMATRIX = DirectX::XMMATRIX;

public:
	static Camera* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// シェイク
	/// </summary>
	void Shake();
	void ShakeStart()	{IsShake = true;}

	//getter
	const XMMATRIX& GetMatProjection()	{return view.matProjection;}
	const XMMATRIX& GetMatView()	{return view.matView;}
	const XMMATRIX& GetViewProjectionMatrix()	{return view.matViewProjection;}

	const Vector3& GetEye() {return view.eye; }
	const Vector3& GetTarget() {return view.target; }
	const Vector3& GetUp() {return view.up; }
	const float& GetAngle()	{return view.angle;}

	//setter
	void SetEye(const Vector3& eye)	{this->view.eye = eye; }
	void SetTarget(const Vector3& target)	{this->view.target = target; }
	void SetUp(const Vector3& up)	{this->view.up = up; }
	void SetAngle(const float& angle)	{this->view.angle = angle;}

	//Reset
	void ReSetAngle()	{this->view.angle = _Angle;}

private:
	//アスペクト用
	Window* window;

	//画角
	const float _Angle = 60.f;

	//シェイク
	const int _Power = 5;
	bool IsShake = false;
	float time = 0.f;
	Vector3 targetBase = {0,0,0};
	Vector3 offset = {0,0,0};

protected:
	ViewProjection view;
};

