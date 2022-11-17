#include "Title.h"

Title::Title(DirectXCommon *dxCommon, Window *window)
	: BaseScene(
		dxCommon,
		window)
{
}

void Title::Application()
{
	BaseScene::Application();
}

void Title::Initialize()
{
	BaseScene::Initialize();
}

void Title::Update()
{
	BaseScene::Update();
}

void Title::Draw()
{
	BaseScene::Draw();

#ifdef _DEBUG
	debugText->Print("Title",0, 0, 3.f);
#endif // _DEBUG

	BaseScene::EndDraw();
}

void Title::Finalize()
{
	BaseScene::Finalize();
}
