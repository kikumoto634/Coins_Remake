#include "ScoreGage.h"

ScoreGage::~ScoreGage()
{
	Finalize();
}

void ScoreGage::Initialize(UINT textureNumber)
{
	BaseSprite::Initialize(textureNumber);
	position = {-20,540};
	size = {600, 200};

	//ƒQ[ƒW
	empty = Sprite::Create(20, position);
	full = Sprite::Create(21, position);
}

void ScoreGage::Update()
{
	BaseSprite::Update();

	//ƒQ[ƒW
	empty->SetPosition(position);
	empty->SetSize(size);

	full->SetPosition({position.x+112.f, position.y});
	full->SetSize({((size.x*(25.f/33.f))*(current/Max)), size.y});
	full->SetTextureRect(0.f,0.f,  ((gageSize*(25.f/32.f))*(current/Max)), 128.f);
}

void ScoreGage::Draw()
{
	empty->Draw();
	full->Draw();
	BaseSprite::Draw();
}

void ScoreGage::Finalize()
{
	BaseSprite::Finalize();
	delete empty;
	empty = nullptr;
	delete full;
	full = nullptr;
}
