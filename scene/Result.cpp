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

	//pressZ
	pressFont = Sprite::Create(22, pressFontPosition);
	pressFontPosition = {580, 450};
	pressFontSize = {120, 45};
}

void Result::Update(bool IsGameOver, bool IsGameClear, int scoreValue)
{
	IsEnd = (IsGameOver || IsGameClear) ? IsEnd = true : IsEnd = false;
	if(!IsEnd) return;


	back->SetPosition(backPosition);
	back->SetSize(backSize);

	font->SetPosition(fontPosition);
	font->SetSize(fontSize);

	score = scoreValue;
	for(int i = 0; i < Num; i++){
		if(scoreNumber[i] == nullptr) {
			int j = score % 10;
			score /= 10;;

			fontNumberPosition[i] = {float(420+(Num-i)*40), 325.f};
			fontNumberSize[i] = {40,100};
			scoreNumber[i] = Sprite::Create(10+j, fontNumberPosition[i]);
			scoreNumber[i]->SetPosition(fontNumberPosition[i]);
			scoreNumber[i]->SetSize(fontNumberSize[i]);
		}
	}

	pressFont->SetPosition(pressFontPosition);
	pressFont->SetSize(pressFontSize);

	alpha = (alpha < 1.f) ? alpha += 1.f/30 : alpha = 1.f;
	back->SetColor({1,1,1,alpha});
	font->SetColor({1,1,1,alpha});
	for(int i = 0; i < Num; i++){
		scoreNumber[i]->SetColor({1,1,1,alpha});
	}
	pressFont->SetColor({1,1,1,alpha});
}

void Result::Draw()
{
	if(!IsEnd) return;
	back->Draw();
	font->Draw();
	for(int i = 0; i < Num; i++){
		scoreNumber[i]->Draw();
	}
	pressFont->Draw();
}

void Result::Finalize()
{
	delete back;
	back = nullptr;

	delete font;
	font = nullptr;

	for(int i = 0; i < Num; i++){
		delete scoreNumber[i];
		scoreNumber[i] = nullptr;
	}

	delete pressFont;
	pressFont = nullptr;
}
