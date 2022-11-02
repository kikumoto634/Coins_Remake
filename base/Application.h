#pragma once
#include "Window.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "SceneManager.h"

#include "TextureManager.h"
#include "Sprite.h"
#include "PostEffect.h"

#include "Camera.h"
#include "WorldTransform.h"

#include "GeometryObjectManager.h"
#include "GeometryObject.h"

#include "FbxLoader.h"
#include "FbxModelManager.h"
#include "FbxModelObject.h"

#ifdef _DEBUG
#include "SceneStopper.h"
#endif // _DEBUG




class Application
{
private:
	//�V���O���g��
	static Application* app;

	Application();
	~Application();

public:
	//�V���O���g��(Application�𕡐����Ӗ��͂Ȃ����߁A�P��̑���)
	static Application* GetInstance();
	static void Delete();

	void Initialize();
	void Run();
	void Finalize();

private:
	void Update();
	void Draw();

private:
#pragma region �ėp�@�\
	Window* window;
	DirectXCommon* dxCommon;
	Input* input;
	Camera* camera = nullptr;
#pragma endregion

#pragma region �X�v���C�g�֘A

	Sprite* sprite = nullptr;
	PostEffect* postEffect = nullptr;

#pragma endregion

#pragma region �I�u�W�F�N�g�֘A
	GeometryObject* object = nullptr;
	WorldTransform worldTransform = {};

	FbxModelManager* modelFbx = nullptr;
	FbxModelObject* objectFbx = nullptr;
	WorldTransform worldTransformFbx;
#pragma endregion

#pragma region �J�����֘A

#pragma endregion

#ifdef _DEBUG
	SceneStopper* sceneStopper = nullptr;
#endif // _DEBUG
};