#include "PlayerHp.h"

PlayerHp::~PlayerHp()
{
	Finalize();
}

void PlayerHp::Initialize(UINT textureNumber)
{
	BaseSprite::Initialize(textureNumber);

	window = Window::GetInstance();
	camera = Camera::GetInstance();

	sprite->SetAnchorpoint({0.5f, 0.5f});

	size = {50,50};

	IsInvisibleState(true);
}

void PlayerHp::Update()
{
	HeartBreak();
	FadeOut();

	BaseSprite::Update();
}

void PlayerHp::Draw()
{


	BaseSprite::Draw();
}

void PlayerHp::Finalize()
{
	BaseSprite::Finalize();
}

void PlayerHp::FadeOut()
{

	if(!IsFade) return;
	IsInvisibleState(false);

	Fadetime += 1.f/60;
	if(Fadetime >= FadeInvisibleTime){
		IsInvisibleState(true);
		Fadetime = 0.f;
		IsFade = false;
		return;
	}
}

void PlayerHp::HeartBreak()
{
	if(!IsBreak) return;
	IsInvisibleState(false);

	BreakTime += 1.f/60;
	if(BreakTime >= BreakInvisibleTime){
		IsInvisibleState(true);
		BreakTime = 0.f;
		IsBreak = false;
		return;
	}
}

Vector2 PlayerHp::ChangeTransformation(Vector3 targetpos)
{
	DirectX::XMMATRIX matViewport = 
	{
		(float)window->GetWindowWidth()/2, 0								  , 0, 0,
		0								 , -((float)window->GetWindowHeight())/2, 0, 0,
		0								 , 0								  , 1, 0, 
		(float)window->GetWindowWidth()/2, (float)window->GetWindowHeight()/2 , 0, 1,
	};
	DirectX::XMMATRIX matViewProjectionViewPort = camera->GetMatView() * camera->GetMatProjection() * matViewport;
	Vector3 positionreticle = Vector3Transform(targetpos, matViewProjectionViewPort);
	return Vector2{positionreticle.x, positionreticle.y};
}

Vector3 PlayerHp::Vector3Transform( Vector3 &v,  DirectX::XMMATRIX &m)
{
	float w = v.x * m.r[0].m128_f32[3] + v.y * m.r[1].m128_f32[3] + v.z * m.r[2].m128_f32[3] + m.r[3].m128_f32[3];

	Vector3 result
	{
		(v.x*m.r[0].m128_f32[0] + v.y*m.r[1].m128_f32[0] + v.z*m.r[2].m128_f32[0] + m.r[3].m128_f32[0])/w,
		(v.x*m.r[0].m128_f32[1] + v.y*m.r[1].m128_f32[1] + v.z*m.r[2].m128_f32[1] + m.r[3].m128_f32[1])/w,
		(v.x*m.r[0].m128_f32[2] + v.y*m.r[1].m128_f32[2] + v.z*m.r[2].m128_f32[2] + m.r[3].m128_f32[2])/w
	};

	return result;
}