#include "Result.h"

Result::~Result()
{
	Finalize();
}

void Result::Initialize(int texNumber)
{
	sprite = Sprite::Create(texNumber, position);

	position = {320, 180};
	size = {640, 360};
}

void Result::Update(bool IsGameEnd)
{
	IsEnd = IsGameEnd;

	sprite->SetPosition(position);
	sprite->SetSize(size);
}

void Result::Draw()
{
	if(!IsEnd) return;
	sprite->Draw();
}

void Result::Finalize()
{
	delete sprite;
	sprite = nullptr;
}
