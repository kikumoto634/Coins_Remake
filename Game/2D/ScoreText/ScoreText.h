#pragma once
#include <string>
#include <Windows.h>
#include <d3d12.h>

#include "Sprite.h"

class ScoreText
{
public:
	static const int maxCharCount = 512;	//最大文字数
	static const int fontWidth = 9;			//フォント画像内1文字内の横幅
	static const int fontHeight = 18;		//フォント画像内1文字内の縦幅
	static const int fontLineCount = 14;	//フォント画像内1行分の文字数
	static const int kBufferSize = 256;		//書式つき文字列展開用バッファサイズ

public:
	//デストラクタ
	~ScoreText();

	//初期化
	void Initialize(UINT texnumber);

	//表示更新
	void Printf(float x, float y, float scale, const char* fmt, ...);

	//描画
	void DrawAll();

private:
	void Print(const std::string& text, float x, float y, float scale = 1.f);

//メンバ変数
public:
	Sprite* sprites[maxCharCount];
	int spriteIndex = 0;
	float posX;
	float posY;
	float scale;
	const char* text;
	// 書式付き文字列展開用バッファ
	char buffer[kBufferSize];
};

