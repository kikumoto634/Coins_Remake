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

#pragma region �X�v���C�g������
	//�X�v���C�g�ÓI������
	Sprite::StaticInitialize(dxCommon, window->GetWindowWidth(), window->GetWindowHeight());
	//����
	sprite = (Sprite::Create(1, Vector2(100.f,100.f)));
	sprite->SetSize(Vector2(100,100));

	//�|�X�g�G�t�F�N�g
	postEffect = (PostEffect::Create(0, Vector2(0.f, 0.f)));

#pragma endregion

#pragma region �I�u�W�F�N�g������

	//Geometry
	worldTransform.Initialize();
	object = GeometryObject::Create(0);

	//Fbx
	worldTransformFbx.Initialize();
	modelFbx = FbxLoader::GetInstance()->LoadModeFromFile("boneTest");
	objectFbx = FbxModelObject::Create(modelFbx);
	objectFbx->PlayAnimation();

#pragma endregion

#pragma region �J����������


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

	worldTransformFbx.translation = {0,-2.5f,0};
	worldTransformFbx.rotation = {0,XMConvertToRadians(90),0};
	worldTransformFbx.UpdateMatrix();

#pragma region ���͏���

	//�X�v���C�g
	{
		if(input->Push(DIK_SPACE)){
			sprite->SetColor({1,0,0,1});
		}
		else{
			sprite->SetColor({1,1,1,1});
		}
	}

	//�􉽊w
	{
		if(input->Push(DIK_RIGHT)){
			worldTransform.rotation.y += XMConvertToRadians(1.f);
		}
		else if(input->Push(DIK_LEFT)){
			worldTransform.rotation.y += XMConvertToRadians(-1.f);
		}
		worldTransform.UpdateMatrix();
	}

	//�J����
	if(input->Push(DIK_D)){
		//���W�ړ�
		//eye.x += 1.f;
		//target.x += 1.f;
	}
	else if(input->Push(DIK_A)){
		//���W�ړ�
		//eye.x += -1.f;
		//target.x += -1.f;
	}

#pragma endregion

#pragma region �X�v���C�g�X�V


#pragma endregion

#pragma region �I�u�W�F�N�g�X�V
	object->Update(worldTransform, camera);
	objectFbx->Update(worldTransformFbx, camera);
#pragma endregion

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
	//object->Draw();
	objectFbx->Draw();

#pragma region 2D�`��
	postEffect->Draw();

	Sprite::SetPipelineState();
	sprite->Draw();
#pragma endregion 2D�`��I��

	//�`��㏈��
	dxCommon->EndDraw();
}

void Application::Finalize()
{
	FBXDelete(objectFbx, modelFbx, worldTransformFbx);
	FbxModelObject::StaticFinalize();
	FbxLoader::GetInstance()->Finalize();

	GeometryDelete(object, worldTransform);
	GeometryObject::StaticFinalize();

	SpriteDelete(sprite);
	Sprite::StaticFinalize();

	window->Finalize();
}
