#include "PlayScene.h"

#include <fstream>
#include <cassert>

using namespace std;

PlayScene::PlayScene(DirectXCommon *dxCommon, Window *window)
	: BaseScene(
		dxCommon,
		window)
{
}

void PlayScene::Application()
{
	/// <summary>
	/// シーンベース
	/// </summary>
	BaseScene::Application();
}

void PlayScene::Initialize()
{
	/// <summary>
	/// シーンベース
	/// </summary>
	BaseScene::Initialize();

	GameSpeed = GameNormalSpeed;

#pragma region 2D初期化
	//スコア表
	scoreText = make_unique<ScoreText>();
	scoreText->Initialize(1);
	//スコアボード
	scoreBoard = make_unique<ScoreBoard>();
	scoreBoard->Initialize(5);
	//スコアゲージ
	scoreGage = make_unique<ScoreGage>();
	scoreGage->Initialize(6);
#pragma endregion 

#pragma region 3D初期化
	//プレイヤー
	player = make_unique<Player>();
	player->Initialize("Player");

	//地面
	for(int i = 0; i < 1;i++){
		GroundPop({0, -150, 200 + (float)i*200});
	}
	//アウトエリア
	for(int i = 0; i < 6;i++){
		OutAreaPop({0, -150, 200 + (float)i*200});
	}

	//天球
	skyDome = make_unique<SkyDome>();
	skyDome->Initialize("skydome");
#pragma endregion

#pragma region 汎用機能初期化
	//ヒットストップ
	hitStop = make_unique<HitStop>();
#pragma endregion

	//リザルト
	result = make_unique<Result>();
	result->Initialize(8);
}

void PlayScene::Update()
{
	/// <summary>
	/// シーンベース
	/// </summary>
	BaseScene::Update();

	//リザルト
	result->Update(player->GetIsDead());

	if(frame % 60 == 0) second += 1;
	//コイン
	CoinPopCommands();

#pragma region 入力処理

	if(input->Trigger(DIK_1)){
		CoinPopReSet();
	}
	else if(input->Trigger(DIK_2)){
		Wall01Pop({0,-150,1000});
	}
	else if(input->Trigger(DIK_3)){
		Wall02Pop({350,-70,1000});
		//Wall02Pop({-350,-70,1000});
	}
	else if(input->Trigger(DIK_4)){
		hitStop->SetStopFrame(3.f);
		hitStop->HitStopStart();
	}
	else if(input->Trigger(DIK_5)){
		camera->ShakeStart();
	}

#pragma endregion

	//ヒットストップ
	if(hitStop->Update(camera)) return;
	//加速
	GameSpeed = GameNormalSpeed;
	if(player->GetIsAccelerator()){
		GameSpeed = GameAcceleratorSpeed;
	}

#pragma region 2D更新
	//スコア
	if(player->GetIsScoreUp()){
		ScoreUp100Pop();
	}
	else if(player->GetIsScoreDown()){
		ScoreDown100Pop();
	}
	score.remove_if([](unique_ptr<ScoreSprite>& sp){
		return sp->GetIsDead();
	});
	for(unique_ptr<ScoreSprite>& sp : score){
		sp->Update();
	}
	//スコア表
	scoreText->Printf(578, 24, 1.5f, "High Score");
	scoreText->Printf(585, 48, 1.5f, "%09d", player->GetScoreCount());
	//スコアボード
	scoreBoard->Update();
	//スコアゲージ
	scoreGage->Update();
#pragma endregion

#pragma region 3D更新
	//プレイヤー
	player->Update(camera, input);
	if(player->GetIsDead()){
		GameSpeed *= player->GetDeadAnimSp();
	}

	//コイン
	coin.remove_if([](unique_ptr<Coins>& obj){
		return obj->GetIsDead();
	});
	for(unique_ptr<Coins>& obj : coin){
		obj->Update(camera);
		obj->SetDepthSp(GameSpeed);
	}

	//地面
	for(unique_ptr<Grounds>& obj : ground){
		obj->Update(camera);
	}
	//アウトエリア
	for(unique_ptr<OutArea>& obj : outArea){
		obj->Update(camera);
		obj->SetDepthSp(GameSpeed);
	}

	//天球
	skyDome->Update(camera);

	//壁
	wall01.remove_if([](unique_ptr<Wall01>& obj){
		return obj->GetIsDead();
	});
	for(unique_ptr<Wall01>& obj : wall01){
		obj->Update(camera, hitStop.get());
		obj->SetDepthSp(GameSpeed);
	}
	wall02.remove_if([](unique_ptr<Wall02>& obj){
		return obj->GetIsDead();
	});
	for(unique_ptr<Wall02>& obj : wall02){
		obj->Update(camera, hitStop.get());
		obj->SetDepthSp(GameSpeed);
	}

#pragma endregion

#pragma region 汎用機能更新
	//衝突判定リスト追加
	if(!player->GetIsDead()){
		collisionManager->SetCollision(player.get());
		for(const std::unique_ptr<Coins>& obj : coin)
		{
			collisionManager->SetCollision(obj.get());
		}
		for(const std::unique_ptr<Wall01>& obj : wall01)
		{
			collisionManager->SetCollision(obj.get());
		}
		for(const std::unique_ptr<Wall02>& obj : wall02)
		{
			collisionManager->SetCollision(obj.get());
		}
	}
#pragma endregion

	/// <summary>
	/// シーンベース
	/// </summary>
	BaseScene::EndUpdate();
}

void PlayScene::Draw()
{
	/// <summary>
	/// シーンベース
	/// </summary>
	BaseScene::Draw();

#pragma region 2D背景
#pragma endregion

#pragma region 3D描画
	//プレイヤー
	player->Draw_3D();

	//コイン
	for(unique_ptr<Coins>& obj : coin){
		obj->Draw();
	}

	//地面
	for(unique_ptr<Grounds>& obj : ground){
		obj->Draw();
	}
	//アウトエリア
	for(unique_ptr<OutArea>& obj : outArea){
		obj->Draw();
	}

	//天球
	skyDome->Draw();

	//壁
	for(unique_ptr<Wall01>& obj : wall01){
		obj->Draw();
	}
	for(unique_ptr<Wall02>& obj : wall02){
		obj->Draw();
	}

#pragma endregion

#pragma region 2D描画UI
	Sprite::SetPipelineState();
	//スコア
	for(unique_ptr<ScoreSprite>& sp : score){
		sp->Draw();
	}

	if(!player->GetIsDead()){
		//スコアボード
		scoreBoard->Draw();
		//スコア表
		scoreText->DrawAll();
	}
	//スコアゲージ
	scoreGage->Draw();

	//プレイヤー
	player->Draw_2D();
	
#pragma endregion 

	//リザルト
	result->Draw();

#ifdef _DEBUG
	debugText->Printf(0,0,1.f,"Camera:Eye	 X:%f Y:%f Z:%f", camera->GetEye().x,camera->GetEye().y,camera->GetEye().z);
	debugText->Printf(0,16,1.f,"Camera:Target X:%f Y:%f Z:%f", camera->GetTarget().x,camera->GetTarget().y,camera->GetTarget().z);

	debugText->Printf(0, 90, 1.f,"frame:%d, second:%d", frame, second);
	debugText->Printf(0, 106, 1.f, "coinNum : %d", coin.size());
	debugText->Printf(0, 122, 1.f, "scoreSpNum : %d", score.size());
	debugText->Printf(0, 138, 1.f, "wall01Num : %d", wall01.size());
	debugText->Printf(0, 154, 1.f, "wall02Num : %d", wall02.size());

	//プレイヤー
	debugText->Printf(0, 600, 1.f, "Player:Pos X:%f Y:%f Z:%f", player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
	debugText->Printf(0, 616, 1.f, "Player:Rot X:%f Y:%f Z:%f", XMConvertToRadians(player->GetRotation().x), XMConvertToRadians(player->GetRotation().y), XMConvertToRadians(player->GetRotation().z));
	debugText->Printf(0, 632, 1.f, "PlayerGetCoin : %d", player->GetCoinCount());
	debugText->Printf(0, 648, 1.f, "PlayerGetSore : %d", player->GetScoreCount());
	debugText->Printf(0, 664, 1.f, "PlayerHp : %d", player->GetHp());
	debugText->Printf(0, 680, 1.f, "PlayerIsAccelerator : %d", player->GetIsAccelerator());
	debugText->Printf(0, 696, 1.f, "PlayerIsAcceleratorGage : %f", player->GetAcceleratorGage());

	//デバックボタン
	debugText->Print("DIK_1 : Coin Appearance",1000,0,1.f);
	debugText->Print("DIK_2 : Wall1 Appearance",1000,16,1.f);
	debugText->Print("DIK_3 : Wall2 Appearance",1000,32,1.f);
	debugText->Print("DIK_4 : HitStop",1000,48,1.f);
	debugText->Print("DIK_5 : CameraShake(Unimplemented)",1000,64,1.f);
	debugText->Print("DIK_6 : PlayerDead",1000,80,1.f);
	debugText->Print("DIK_7 : AcceleratorGage MAX",1000,96,1.f);

#endif // _DEBUG

	/// <summary>
	/// シーンベース
	/// </summary>
	BaseScene::EndDraw();
}

void PlayScene::Finalize()
{
	/// <summary>
	/// シーンベース
	/// </summary>
	BaseScene::Finalize();

#pragma region 3D後処理
	//プレイヤー
	player->Finalize();

	//コイン
	for(unique_ptr<Coins>& obj : coin){
		obj->Finalize();
	}

	//地面
	for(unique_ptr<Grounds>& obj : ground){
		obj->Finalize();
	}
	//アウトエリア
	for(unique_ptr<OutArea>& obj : outArea){
		obj->Finalize();
	}

	//天球
	skyDome->Finalize();

	//壁0
	for(unique_ptr<Wall01>& obj : wall01){
		obj->Finalize();
	}
	for(unique_ptr<Wall02>& obj : wall02){
		obj->Finalize();
	}

#pragma endregion

#pragma region 2D後処理
	//スコア
	for(unique_ptr<ScoreSprite>& sp : score){
		sp->Finalize();
	}	
	//スコア表
	scoreText->Finalize();
	//スコアボード
	scoreBoard->Finalize();
	//スコアゲージ
	scoreGage->Finalize();
#pragma endregion 

	result->Finalize();
}

#pragma region コイン処理
void PlayScene::LoadCoinPopData()
{
	//file開く
	ifstream file;
	file.open("Resources/csv/sample01.csv");
	assert(file.is_open());

	//file培養を文字列ストリームにコピー
	coinPopCommands << file.rdbuf();
	file.close();
}
void PlayScene::CoinPopCommands()
{
	//待機処理
	if(IsWait){
		waitTime--;
		if(waitTime <= 0){
			//待機完了
			IsWait = false;
		}
		return;
	}

	//一行分の文字列を入れる変数
	string line;

	//コマンドループ
	while(getline(coinPopCommands, line)){
		//一行分のっ文字列をストリームに変換して解析しやすく
		istringstream line_stream(line);

		string word;
		//区切りで行の銭湯文字列取得
		getline(line_stream, word, ',');

		//"//"から始まるのはcomment
		if(word.find("//") == 0){
			//飛ばす
			continue;
		}

		//POPコマンド
		if(word.find("POP") == 0){
			//X座標
			getline(line_stream, word, ',');
			float x = (float)atof(word.c_str());

			//Y座標
			getline(line_stream, word, ',');
			float y = (float)atof(word.c_str());

			//Z座標
			getline(line_stream, word, ',');
			float z = (float)atof(word.c_str());

			//POP
			CoinPop(Vector3(x,y,z));
		}
		else if(word.find("WAIT") == 0){
			getline(line_stream,word, ',');

			//待ち時間
			int32_t waitTime = atoi(word.c_str());

			//待機開始
			IsWait = true;
			this->waitTime = waitTime;

			break;
		}
		else if(word.find("LOOP") == 0){
			CoinPopReSet();
			break;
		}
	}
}
void PlayScene::CoinPop(Vector3 pos)
{
	unique_ptr<Coins> newCoin = make_unique<Coins>();
	newCoin->Initialize("coin");
	newCoin->SetVector3(pos);

	coin.push_back(move(newCoin));
}
void PlayScene::CoinPopReSet()
{
	coinPopCommands = {};
	LoadCoinPopData();
}
#pragma endregion

void PlayScene::GroundPop(Vector3 position)
{
	unique_ptr<Grounds> newobj = make_unique<Grounds>();
	newobj->Initialize("ground");
	newobj->SetVector3(position);

	ground.push_back(move(newobj));
}

void PlayScene::OutAreaPop(Vector3 position)
{
	unique_ptr<OutArea> newobj = make_unique<OutArea>();
	newobj->Initialize("OutArea");
	newobj->SetVector3(position);

	outArea.push_back(move(newobj));
}

void PlayScene::Wall01Pop(Vector3 position)
{
	unique_ptr<Wall01> newobj = make_unique<Wall01>();
	newobj->Initialize("Wall01");
	newobj->SetVector3(position);

	wall01.push_back(move(newobj));
}
void PlayScene::Wall02Pop(Vector3 position)
{
	unique_ptr<Wall02> newobj = make_unique<Wall02>();
	newobj->Initialize("Wall02");
	newobj->SetVector3(position);

	wall02.push_back(move(newobj));
}

void PlayScene::ScoreUp100Pop()
{
	unique_ptr<ScoreSprite> newsp = make_unique<ScoreSprite>();
	newsp->Initialize(2);
	Vector2 target = newsp->ChangeTransformation(Vector3(player->GetPosition().x, player->GetPosition().y+30, player->GetPosition().z));
	newsp->SetVector2(target);

	score.push_back(move(newsp));
}

void PlayScene::ScoreDown100Pop()
{
	unique_ptr<ScoreSprite> newsp = make_unique<ScoreSprite>();
	newsp->Initialize(3);
	Vector2 target = newsp->ChangeTransformation(Vector3(player->GetPosition().x, player->GetPosition().y+30, player->GetPosition().z));
	newsp->SetVector2(target);

	score.push_back(move(newsp));
}

