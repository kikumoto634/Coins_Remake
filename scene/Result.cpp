#include "Result.h"

Result::~Result()
{
	Finalize();
}

void Result::Initialize(int BackTexNumber, int fonrtexNumber)
{
	//バック
	back = Sprite::Create(BackTexNumber, backPosition);
	backPosition = {320, 180};
	backSize = {640, 360};

	//フォント
	font = Sprite::Create(fonrtexNumber, fontPosition);
	fontPosition = {520, 200};
	fontSize = {240, 90};
}

void Result::Update(bool IsGameEnd)
{
	IsEnd = IsGameEnd;
	if(!IsEnd) return;


	back->SetPosition(backPosition);
	back->SetSize(backSize);

	font->SetPosition(fontPosition);
	font->SetSize(fontSize);

	alpha = (alpha < 1.f) ? alpha += 1.f/30 : alpha = 1.f;
	back->SetColor({1,1,1,alpha});
	font->SetColor({1,1,1,alpha});
}

void Result::Draw()
{
	if(!IsEnd) return;
	back->Draw();
	font->Draw();
}

void Result::Finalize()
{
	delete back;
	back = nullptr;

	delete font;
	font = nullptr;
}
