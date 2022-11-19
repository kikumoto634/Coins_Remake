#include "Title.h"

using namespace std;

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

#pragma region _2Dモデル初期化
	titleLogo = make_unique<BaseSprite>();
	titleLogo->Initialize(7);
	titleLogo->SetVector2(LogoPos);
	titleLogo->SetSize(LogoSize);

	pressText = make_unique<BaseSprite>();
	pressText->Initialize(22);
	pressText->SetVector2(pressTextPos);
	pressText->SetSize(pressTextSize);

#pragma endregion

#pragma region _3Dモデル初期化
	//プレイヤー
	playerObj = make_unique<Player>();
	playerObj->Initialize("Player");

	//天球
	skyDome = make_unique<SkyDome>();
	skyDome->Initialize("skydome");
	skyDome->SetRotation({0, 180, 0});

	//地面
	GroundPop({0, -150, 600});
	//アウトエリア
	for(int i = 0; i < 7;i++){
		OutAreaPop({0, -150, 200 - (float)i*200});
	}
	for(unique_ptr<OutArea>& obj : outArea){
		obj->SetDeletePosZ(-1000);
		obj->SetPopPosZ(400);
	}
#pragma endregion

	//カメラ
	camera->SetTarget({125,-90,-50});
	camera->SetEye({-86, -130,250});

#ifdef _DEBUG
	target = camera->GetTarget();
	eye = camera->GetEye();
#endif // _DEBUG

}

void Title::Update()
{
	BaseScene::Update();

#pragma region 入力
	
	//シーン遷移
	if(input->Push(DIK_Z)){
		IsStart = true;
	}

	/// <summary>
	/// スタートアニメーション開始
	/// </summary>
	StartAnim();

#ifdef _DEBUG
	//target
	if(input->Push(DIK_D)) target.y += 1.f;
	else if(input->Push(DIK_A)) target.y -= 1.f;
	if(input->Push(DIK_S)) target.z -= 1.f;
	else if(input->Push(DIK_W)) target.z += 1.f;

	//eye
	if(input->Push(DIK_RIGHT)) eye.y += 1.f;
	else if(input->Push(DIK_LEFT)) eye.y -= 1.f;
	if(input->Push(DIK_DOWN)) eye.z -= 1.f;
	else if(input->Push(DIK_UP)) eye.z += 1.f;

	//player
	Vector3 pos = playerObj->GetPosition();
	if(input->Push(DIK_Z)){
		pos.z += 1.f;
	}
	else if(input->Push(DIK_C)){
		pos.z -= 1.f;
	}
	playerObj->SetVector3(pos);

	camera->SetTarget(target);
	camera->SetEye(eye);
#endif // _DEBUG
#pragma endregion

#pragma region _2Dモデル更新
	TitleLogoMove();
	titleLogo->Update();

	pressText->Update();
#pragma endregion

#pragma region _3Dモデル更新
	//プレイヤー
	playerObj->Update(camera);

	//天球
	skyDome->Update(camera);

	//地面
	for(unique_ptr<Grounds>& obj : ground){
		obj->Update(camera);
	}
	//アウトエリア
	for(unique_ptr<OutArea>& obj : outArea){
		obj->Update(camera);
		obj->SetDepthSp(GameSpeed);
	}
#pragma endregion

	BaseScene::EndUpdate();
}

void Title::Draw()
{
	BaseScene::Draw();

#pragma region _3Dモデル描画
	//プレイヤー
	playerObj->Draw();

	//天球
	skyDome->Draw();

	//地面
	for(unique_ptr<Grounds>& obj : ground){
		obj->Draw();
	}
	//アウトエリア
	for(unique_ptr<OutArea>& obj : outArea){
		obj->Draw();
	}
#pragma endregion

#pragma region _2DUI描画
	Sprite::SetPipelineState();
	//タイトルロゴ
	titleLogo->Draw();

	pressText->Draw();

#ifdef _DEBUG
	debugText->Print("Title",0, 0, 3.f);

	debugText->Printf(0, 160, 1.f, "CameraTarget X:%f, Y:%f,Z:%f", camera->GetTarget().x, camera->GetTarget().y, camera->GetTarget().z);
	debugText->Printf(0, 176, 1.f, "Target X:%f, Y:%f,Z:%f", target.x, target.y, target.z);
	debugText->Printf(0, 192, 1.f, "CameraEye X:%f, Y:%f,Z:%f", camera->GetEye().x, camera->GetEye().y, camera->GetEye().z);
	debugText->Printf(0, 208, 1.f, "Eye X:%f, Y:%f,Z:%f", eye.x, eye.y, eye.z);

	debugText->Printf(0, 224, 1.f, "PlayerPos X:%f, Y:%f,Z:%f", playerObj->GetPosition().x, playerObj->GetPosition().y, playerObj->GetPosition().z);
#endif // _DEBUG
#pragma endregion

	BaseScene::EndDraw();
}

void Title::Finalize()
{
	BaseScene::Finalize();

#pragma region _2D後処理
	titleLogo->Finalize();
	pressText->Finalize();
#pragma endregion

#pragma region _3Dモデル後処理
	//プレイヤー
	playerObj->Finalize();
	
	//天球
	skyDome->Finalize();

	//地面
	for(unique_ptr<Grounds>& obj : ground){
		obj->Finalize();
	}
	//アウトエリア
	for(unique_ptr<OutArea>& obj : outArea){
		obj->Finalize();
	}
#pragma endregion
}

void Title::GroundPop(Vector3 position)
{
	unique_ptr<Grounds> newobj = make_unique<Grounds>();
	newobj->Initialize("ground");
	newobj->SetVector3(position);

	ground.push_back(move(newobj));
}

void Title::OutAreaPop(Vector3 position)
{
	unique_ptr<OutArea> newobj = make_unique<OutArea>();
	newobj->Initialize("OutArea");
	newobj->SetVector3(position);

	outArea.push_back(move(newobj));
}

void Title::TitleLogoMove()
{
	LogoTime = (LogoTime < 1.f) ? LogoTime += 1.f/180 : LogoTime = 0.f, LogoPos = LogoStartPos;
	float ease = -(cosf(3.14159265f * LogoTime) - 1.f)/2.f;

	LogoPos.x = ((1.f-ease)*(1.f-ease) * LogoStartPos.x) + (2 * (1.f-ease) * ease * LogoEndPos.x) + (ease*ease * LogoStartPos.x);
	LogoPos.y = ((1.f-ease)*(1.f-ease) * LogoStartPos.y) + (2 * (1.f-ease) * ease * LogoEndPos.y) + (ease*ease * LogoStartPos.y);

	titleLogo->SetVector2(LogoPos);
}

void Title::StartAnim()
{
	if(!IsStart) return;

	//プレイヤー移動
	startTime = (startTime < 1.f) ? startTime += 1.f/120 : startTime = 1.f;

	Vector3 pos = playerObj->GetPosition();

	float c1 = 1.70158f;
	float c3 = c1 + 1.f;
	float ease = c3 * startTime * startTime * startTime - c1 * startTime * startTime;

	pos.z = (1.f - ease) * 199.f + ease * 270.f;


	playerObj->SetVector3(pos);

	if(playerObj->GetPosition().z == 270.f) IsSceneChange = true;
}
