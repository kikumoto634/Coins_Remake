#include "ScoreBoard.h"

ScoreBoard::~ScoreBoard()
{
	Finalize();
}

void ScoreBoard::Initialize(UINT textureNumber)
{
	BaseSprite::Initialize(textureNumber);
	position = {560,0};
	size = {170, 100};
}

void ScoreBoard::Update()
{
	BaseSprite::Update();
}

void ScoreBoard::Draw()
{
	BaseSprite::Draw();
}

void ScoreBoard::Finalize()
{
	BaseSprite::Finalize();
}
