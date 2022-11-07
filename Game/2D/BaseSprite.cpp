#include "BaseSprite.h"

void BaseSprite::Initialize(UINT textureNumber)
{
	sprite = Sprite::Create(textureNumber, position);
}

void BaseSprite::Update()
{
	sprite->SetPosition(position);
	sprite->SetSize(size);
}

void BaseSprite::Draw()
{
	sprite->Draw();
}

void BaseSprite::Finalize()
{
	delete sprite;
	sprite = nullptr;
}
