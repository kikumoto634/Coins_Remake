#pragma once
#include "Window.h"
#include "Vector3.h"

#include "ViewProjection.h"

#include <DirectXMath.h>

/// <summary>
/// �J����
/// </summary>
class Camera
{
public:
	using XMMATRIX = DirectX::XMMATRIX;

public:
	static Camera* GetInstance();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update();

	/// <summary>
	/// �V�F�C�N
	/// </summary>
	void Shake();
	void ShakeStart()	{IsShake = true;}

	
	/// <summary>
	/// ����p
	/// </summary>
	void AngleMove(float targetAngle);
	void ReSetAngle() {view.angle = _Angle;}

	//getter
	const XMMATRIX& GetMatProjection()	{return view.matProjection;}
	const XMMATRIX& GetMatView()	{return view.matView;}
	const XMMATRIX& GetViewProjectionMatrix()	{return view.matViewProjection;}

	const Vector3& GetEye() {return view.eye; }
	const Vector3& GetTarget() {return view.target; }
	const Vector3& GetUp() {return view.up; }
	const float& GetAngle()	{return view.angle;}
	const float& GetIniAngle() {return _Angle;}

	//setter
	void SetEye(const Vector3& eye)	{this->view.eye = eye; }
	void SetTarget(const Vector3& target)	{this->view.target = target; }
	void SetUp(const Vector3& up)	{this->view.up = up; }
	void SetAngle(const float& angle)	{this->view.angle = angle;}

private:
	//�A�X�y�N�g�p
	Window* window;

	//��p
	const float _Angle = 60.f;

	//�V�F�C�N
	float _Power = 1.f;
	bool IsShake = false;
	float time = 0.f;
	Vector3 targetBase = {0,0,0};
	Vector3 offset = {0,0,0};

	//����p
	bool IsAngleFlag = false;

protected:
	ViewProjection view;
};

