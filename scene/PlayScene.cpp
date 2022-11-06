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

#pragma region 2D初期化
#pragma endregion 

#pragma region 3D初期化
	//プレイヤー
	player = make_unique<Player>();
	player->Initialize("player");

	//コイン
	LoadCoinPopData();

	//地面
	for(int i = 0; i < 6;i++){
		GroundPop({0, -150, 200 + (float)i*200});
	}
#pragma endregion

#pragma region 汎用機能初期化
#pragma endregion
}

void PlayScene::Update()
{
	/// <summary>
	/// シーンベース
	/// </summary>
	BaseScene::Update();
	frame += 1;

#pragma region 入力処理
#pragma endregion

#pragma region 2D更新
#pragma endregion

#pragma region 3D更新
	//プレイヤー
	player->Update(camera, input);

	//コイン
	UpdateCoinPopCommands();
	coin.remove_if([](unique_ptr<Coins>& obj){
		return obj->GetIsDead();
	});
	for(unique_ptr<Coins>& obj : coin){
		obj->Update(camera);
	}

	//地面
	for(unique_ptr<Grounds>& obj : ground){
		obj->Update(camera);
	}
#pragma endregion

#pragma region 汎用機能更新
	//衝突判定リスト追加
	collisionManager->SetCollision(player.get());
	for(const std::unique_ptr<Coins>& obj : coin)
	{
		collisionManager->SetCollision(obj.get());
	}
#pragma endregion

#ifdef _DEBUG
	debugText->Printf(0,0,1.f,"Camera:Eye	 X:%f Y:%f Z:%f", camera->GetEye().x,camera->GetEye().y,camera->GetEye().z);
	debugText->Printf(0,16,1.f,"Camera:Target X:%f Y:%f Z:%f", camera->GetTarget().x,camera->GetTarget().y,camera->GetTarget().z);
	debugText->Printf(0, 48, 1.f, "Player:Pos X:%f Y:%f Z:%f", player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);

	debugText->Printf(0, 90, 1.f,"frame:%d, second:%d", frame, frame/60);
#endif // _DEBUG

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
	player->Draw();

	//コイン
	for(unique_ptr<Coins>& obj : coin){
		obj->Draw();
	}

	//地面
	for(unique_ptr<Grounds>& obj : ground){
		obj->Draw();
	}
#pragma endregion

#pragma region 2D描画UI
	Sprite::SetPipelineState();
#pragma endregion 

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

#pragma endregion

#pragma region 2D後処理

#pragma endregion 
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
void PlayScene::UpdateCoinPopCommands()
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
	}
}
void PlayScene::CoinPop(Vector3 pos)
{
	unique_ptr<Coins> newCoin = make_unique<Coins>();
	newCoin->Initialize("coin");
	newCoin->SetVector3(pos);

	coin.push_back(move(newCoin));
}
#pragma endregion

void PlayScene::GroundPop(Vector3 position)
{
	unique_ptr<Grounds> newobj = make_unique<Grounds>();
	newobj->Initialize("ground");
	newobj->SetVector3(position);

	ground.push_back(move(newobj));
}
