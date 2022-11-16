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
}

void ScoreGage::Update()
{
	BaseSprite::Update();
}

void ScoreGage::Draw()
{
	BaseSprite::Draw();
}

void ScoreGage::Finalize()
{
	BaseSprite::Finalize();
}
