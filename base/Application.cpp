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

	//Input初期化
	input->Initialize(window->GetHwnd());

	//テクスチャ
	TextureManager::GetInstance()->Initialize(dxCommon);
	TextureManager::Load(0, "Texture.jpg");
	TextureManager::Load(1, "white1x1.png");

	//カメラ
	camera->Initialize();

	//Geometry
	GeometryObjectManager::GetInstance()->CreateBuffer();
	GeometryObject::StaticInitialize(dxCommon);
	
	//FBX
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
	FbxModelObject::StaticInitialize(dxCommon);

#pragma endregion

#ifdef _DEBUG
	//一時停止
	sceneStopper = SceneStopper::GetInstance();

#endif // _DEBUG
}

void Application::Update()
{
#ifdef _DEBUG

#pragma region 一時停止
	//入力
	if(input->Trigger(DIK_F1)){
		if(!sceneStopper->GetIsSceneStop()){
			sceneStopper->SetIsSceneStop(true);
		}
		else if(sceneStopper->GetInstance()){
			sceneStopper->SetIsSceneStop(false);
		}
	}
	//停止
	if(sceneStopper->GetIsSceneStop()) return;
#pragma endregion

#endif // _DEBUG

#pragma region 汎用機能更新
	//入力情報更新
	input->Update();
	//カメラ
	camera->Update();
#pragma endregion
}

void Application::Draw()
{
	//描画前処理
	dxCommon->BeginDraw();


	//描画後処理
	dxCommon->EndDraw();
}

void Application::Finalize()
{
	window->Finalize();
}
