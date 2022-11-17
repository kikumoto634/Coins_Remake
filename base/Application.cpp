#include "Application.h"

#include "Title.h"
#include "PlayScene.h"

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

	scene = make_unique<Title>(dxCommon, window);
	scene->Application();
	sceneName = "Title";
}


Application::~Application()
{
}

void Application::Run()
{
	MSG msg{};//メッセージ
	while (true)
	{
		if(PeekMessage(&msg, nullptr,0, 0,PM_REMOVE)){
			TranslateMessage(&msg);	//キー入力メッセージの処理
			DispatchMessage(&msg);	//プロシージャにメッセージを送る
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
#pragma region 汎用機能初期化
	//Window生成
	window->Create("GiliraEngine", 1280, 720);

	//DirectXCommon
	dxCommon->Initialize(window);

	//テクスチャ
	TextureManager::GetInstance()->Initialize(dxCommon);
	TextureManager::Load(0, "white1x1.png");
	TextureManager::Load(1, "texfont.png");
	TextureManager::Load(2, "Score/add100.png");
	TextureManager::Load(3, "Score/sub100.png");
	TextureManager::Load(4, "Hp/Heart_Still.png");
	TextureManager::Load(5, "Score/ScoreBoard.png");
	TextureManager::Load(6, "Score/ScoreGage.png");
	TextureManager::Load(7, "Title/Title.png");
	TextureManager::Load(8, "Result/ResultBack.png");
	Sprite::StaticInitialize(dxCommon, window->GetWindowWidth(), window->GetWindowHeight());

	//Geometry
	GeometryObjectManager::GetInstance()->CreateBuffer();
	GeometryObject::StaticInitialize(dxCommon);
	
	//FBX
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
	FbxModelObject::StaticInitialize(dxCommon);

#pragma endregion

	scene->Initialize();
}

void Application::Update()
{
	//シーン遷移
	if(scene->GetIsSceneChange()){
		if(sceneName == "Title"){
			scene->Finalize();
			scene = make_unique<PlayScene>(dxCommon, window);
			scene->Application();
			scene->Initialize();
			sceneName = "Play";
			scene->ResetIsSceneChange();
		}
		else if(sceneName == "Play"){
			scene->Finalize();
			scene = make_unique<Title>(dxCommon, window);
			scene->Application();
			scene->Initialize();
			sceneName = "Title";
			scene->ResetIsSceneChange();
		}
	}

	scene->Update();
	scene->EndUpdate();
}

void Application::Draw()
{
	//描画前処理
	dxCommon->BeginDraw();

	Sprite::SetPipelineState();
	scene->Draw();

	//描画後処理
	dxCommon->EndDraw();
}

void Application::Finalize()
{
	FbxModelObject::StaticFinalize();
	FbxLoader::GetInstance()->Finalize();
	GeometryObject::StaticFinalize();
	Sprite::StaticFinalize();

	scene->Finalize();
	delete scene.get();

	window->Finalize();
}
