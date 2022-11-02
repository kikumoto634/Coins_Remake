#include "Application.h"
#include "SafeDelete.h"

Application* Application::app = nullptr;

using namespace std;

Application *Application::GetInstance()
{
	if(!app)
	{
		app = new Application();
	}
	return app;
}

void Application::Delete()
{
	if(app){
		delete app;
		app = nullptr;
	}
}

Application::Application()
{
	window = Window::GetInstance();
	dxCommon = DirectXCommon::GetInstance();
	input = Input::GetInstance();
	camera = Camera::GetInstance();
}

Application::~Application()
{
}

void Application::Run()
{
	MSG msg{};//���b�Z�[�W
	while (true)
	{
		if(PeekMessage(&msg, nullptr,0, 0,PM_REMOVE)){
			TranslateMessage(&msg);	//�L�[���̓��b�Z�[�W�̏���
			DispatchMessage(&msg);	//�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
		}
		if(msg.message == WM_QUIT) {
			break;
		}

		Update();
		Draw();
	}
}

void Application::Initialize()
{
#pragma region �ėp�@�\������
	//Window����
	window->Create("GiliraEngine", 1280, 720);

	//DirectXCommon
	dxCommon->Initialize(window);

	//Input������
	input->Initialize(window->GetHwnd());

	//�e�N�X�`��
	TextureManager::GetInstance()->Initialize(dxCommon);
	TextureManager::Load(0, "Texture.jpg");
	TextureManager::Load(1, "white1x1.png");

	//�J����
	camera->Initialize();

	//Geometry
	GeometryObjectManager::GetInstance()->CreateBuffer();
	GeometryObject::StaticInitialize(dxCommon);
	
	//FBX
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
	FbxModelObject::StaticInitialize(dxCommon);

#pragma endregion

#ifdef _DEBUG
	//�ꎞ��~
	sceneStopper = SceneStopper::GetInstance();

#endif // _DEBUG
}

void Application::Update()
{
#ifdef _DEBUG

#pragma region �ꎞ��~
	//����
	if(input->Trigger(DIK_F1)){
		if(!sceneStopper->GetIsSceneStop()){
			sceneStopper->SetIsSceneStop(true);
		}
		else if(sceneStopper->GetInstance()){
			sceneStopper->SetIsSceneStop(false);
		}
	}
	//��~
	if(sceneStopper->GetIsSceneStop()) return;
#pragma endregion

#endif // _DEBUG

#pragma region �ėp�@�\�X�V
	//���͏��X�V
	input->Update();
	//�J����
	camera->Update();
#pragma endregion
}

void Application::Draw()
{
	//�`��O����
	dxCommon->BeginDraw();


	//�`��㏈��
	dxCommon->EndDraw();
}

void Application::Finalize()
{
	window->Finalize();
}
