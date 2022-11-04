#pragma once
#include <string>
#include <Windows.h>
#include <d3d12.h>

#include "Sprite.h"

//�f�o�b�N�p������N���X�̒�`
class DebugText
{
public:

	static const int maxCharCount = 512;	//�ő啶����
	static const int fontWidth = 9;			//�t�H���g�摜��1�������̉���
	static const int fontHeight = 18;		//�t�H���g�摜��1�������̏c��
	static const int fontLineCount = 14;	//�t�H���g�摜��1�s���̕�����
	static const int kBufferSize = 256;		//������������W�J�p�o�b�t�@�T�C�Y

	~DebugText();

	void Initialize(UINT texnumber);

	void Print(const std::string& text, float x, float y, float scale = 1.f);
	void Printf(float x, float y, float scale, const char* fmt, ...);

	void DrawAll();

private:
	Sprite* sprites[maxCharCount];
	int spriteIndex = 0;
	float posX;
	float posY;
	float scale;
	const char* text;
	// �����t��������W�J�p�o�b�t�@
	char buffer[kBufferSize];
};