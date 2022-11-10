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
	//�A�X�y�N�g�p
	Window* window;

	const float _Angle = 60.f;

protected:
	ViewProjection view;
};

