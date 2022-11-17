#pragma once
#include "Window.h"
#include "DirectXCommon.h"

#include "TextureManager.h"
#include "Sprite.h"

#include "GeometryObjectManager.h"
#include "GeometryObject.h"

#include "FbxLoader.h"
#include "FbxModelManager.h"
#include "FbxModelObject.h"

#include "BaseScene.h"


#include "Sprite.h"



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
#pragma endregion

	std::unique_ptr<BaseScene> scene;
	std::string sceneName = "";

};