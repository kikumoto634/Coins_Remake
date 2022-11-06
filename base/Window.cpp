#include "Window.h"

#pragma comment(lib, "winmm.lib")

wchar_t Window::kWindowClassName[] = L"DirectXGame";


Window::Window()
{
}

Window::~Window()
{
}

Window *Window::GetInstance()
{
	static Window instance;
	return &instance;
}

void Window::Create(const std::string& name, const int width, const int height)
{
	this->name = name;
	this->window_width = width;
	this->window_height = height;

	//�E�B���h�E�N���X�ݒ�
	//WNDCLASSEX w{};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc;		//�E�B���h�E�v���V�[�W���ݒ�
	w.lpszClassName = kWindowClassName;			//�E�B���h�E�N���X��
	w.hInstance = GetModuleHandle(nullptr);		//�E�B���h�E�n���h��
	w.hCursor = LoadCursor(NULL, IDC_ARROW);	//�J�[�\���w��

	//�E�B���h�E�N���X��OS�ɓo�^����
	RegisterClassEx(&w);
	//�E�B���h�E�T�C�Y{ X���W Y���W ���� �c��}
	RECT wrc = {0, 0, window_width, window_height};
	//�����ŃT�C�Y��␳����
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	///�E�B���h�E�I�u�W�F�N�g�̐���
	wchar_t wName[256];
	MultiByteToWideChar(CP_ACP, 0, this->name.c_str(), -1, wName, _countof(wName));

	hwnd = CreateWindow(
		w.lpszClassName,			//�N���X��
		wName,				//�^�C�g���o�[����
		WS_OVERLAPPEDWINDOW,		//�W���I�ȃE�B���h�E�X�^�C��
		CW_USEDEFAULT,				//�\��X���W(OS�ɔC����)
		CW_USEDEFAULT,				//�\��Y���W(OS�ɔC����)
		wrc.right  - wrc.left,		//�E�B���h�E����
		wrc.bottom - wrc.top,		//�E�B���h�E�c��
		nullptr,					//�e�E�B���h�E�n���h��
		nullptr,					//���j���[�n���h��
		w.hInstance,				//�Ăяo���A�v���P�[�V�����n���h��
		nullptr						//�I�v�V����
	);
	//�E�B���h�E��\����Ԃɂ���
	ShowWindow(hwnd, SW_SHOW);

	//�V�X�e���^�C�}�[�̕���\��������
	timeBeginPeriod(1);
}

void Window::Finalize()
{
	///�E�B���h�E�N���X��o�^����
	UnregisterClass(w.lpszClassName, w.hInstance);
}

LRESULT Window::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//���b�Z�[�W�ɉ����ăQ�[���ŗL�̏������s��
	switch (msg){
		//�E�B���h�E���j�����ꂽ
	case WM_DESTROY:
		//OS�ɑ΂��āA�A�v���̏I����`����
		PostQuitMessage(0);
		return 0;
	}

	//�W���̃��b�Z�[�W�������s��
	return DefWindowProc(hwnd, msg, wparam, lparam);
}
