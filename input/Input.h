#pragma once

//�L�[�{�[�h����
#define DIRECTINPUT_VERSION 0x0800	//DirectInput�̃o�[�W�����w��
#include <dinput.h>
const int KeyNum = 256;

class Input
{
public:
	Input();
	~Input() = default;

	static Input* GetInstance();

	//������
	void Initialize(HWND hwnd);

	//�X�V
	void Update();

#pragma region �L�[�{�[�h����
	bool Push(int keyNumber);
	bool Trigger(int keyNumber);
#pragma endregion

private:
#pragma region �L�[�{�[�h
	//�L�[�{�[�h�f�o�C�X
	IDirectInputDevice8* keyboard = nullptr;
	//�L�[���
	BYTE key[KeyNum] = {};
	//�O�t���[���L�[���
	BYTE prekey[KeyNum] = {};
#pragma endregion
};

