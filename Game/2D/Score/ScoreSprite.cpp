#include "ScoreSprite.h"

void ScoreSprite::Initialize(UINT textureNumber)
{
	BaseSprite::Initialize(textureNumber);

	window = Window::GetInstance();
}

void ScoreSprite::Update()
{
	FadeOut();

	BaseSprite::Update();
}

void ScoreSprite::Draw()
{


	BaseSprite::Draw();
}

void ScoreSprite::Finalize()
{
	BaseSprite::Finalize();
}

void ScoreSprite::FadeOut()
{
	//時間
	time += 1.f/60;
	if(time >= InvisibleTime){
		IsDead = true;
	}

	//移動
	position.y -= 1.f;

	//フェードアウト
	alpha -= 1.f/120;
	sprite->SetColor({1,1,1,alpha});
}

Vector2 ScoreSprite::ChangeTransformation(Vector3 targetpos)
{
	DirectX::XMMATRIX matViewport = 
	{
		(float)window->GetWindowWidth()/2, 0							, 0, 0,
		0						  , (float)-window->GetWindowHeight()/2, 0, 0,
		0						  , 0							, 1, 0, 
		(float)window->GetWindowWidth()/2, (float)window->GetWindowHeight()/2 , 0, 1,
	};
	DirectX::XMMATRIX matViewProjectionViewPort = matView * matViewProjection * matViewport;
	Vector3 positionreticle = Vector3Transform(targetpos, matViewProjectionViewPort);
	return Vector2{positionreticle.x, positionreticle.y};
}

Vector3 ScoreSprite::Vector3Transform( Vector3 &v,  DirectX::XMMATRIX &m)
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