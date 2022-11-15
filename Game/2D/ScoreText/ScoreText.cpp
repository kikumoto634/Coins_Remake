#include "ScoreText.h"

ScoreText::~ScoreText()
{
	for(int i = 0; i < _countof(sprites); i++)
	{
		//�X�v���C�g�����
		delete sprites[i];
		sprites[i] = nullptr;
	}
}

void ScoreText::Initialize(UINT texnumber)
{
	for(int i = 0; i < _countof(sprites); i++)
	{
		//�X�v���C�g����
		sprites[i] = new Sprite();
		//�X�v���C�g������������
		sprites[i]->Initialize(texnumber);
		sprites[i]->SetColor({1,1,1,1});
	}
}

void ScoreText::Printf(float x, float y, float scale, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	int w = vsnprintf(buffer, kBufferSize - 1, fmt, args);

	Print(buffer, x, y, scale);

	va_end(args);
}

void ScoreText::DrawAll()
{
	//���ׂĂ̕����̃X�v���C�g�ɂ���
	for(int i = 0; i < spriteIndex; i++)
	{
		//�X�v���C�g�`��
		sprites[i]->Draw();
	}
	spriteIndex = 0;
}

void ScoreText::Print(const std::string &text, float x, float y, float scale)
{
	this->posX = x;
	this->posY = y;
	this->scale = scale;
	this->text = text.c_str();

	//���ׂĂ̕����ɂ���
	for(int i = 0; i < (int)text.size(); i++)
	{
		//�ő啶����
		if(spriteIndex >= maxCharCount)
		{
			break;
		}

		//�ꕶ�����o��(��ASCII�R�[�h�ł������藧���Ȃ�)
		const unsigned char& character = this->text[i];

		int fontIndex = character - 32;
		if(character >= 0x7f)
		{
			fontIndex = 0;
		}

		int fontIndexY = fontIndex / fontLineCount;
		int fontIndexX = fontIndex % fontLineCount;

		//���W�v�Z
		sprites[spriteIndex]->SetPosition({posX + fontWidth * this->scale * i, posY});
		sprites[spriteIndex]->SetTextureRect((float)fontIndexX * fontWidth, (float)fontIndexY * fontHeight, (float)fontWidth, (float)fontHeight);
		sprites[spriteIndex]->SetSize({fontWidth * this->scale, fontHeight * this->scale});

		//��������i�߂�
		spriteIndex++;
	}
}
