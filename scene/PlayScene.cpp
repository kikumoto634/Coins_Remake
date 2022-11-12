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
	/// �V�[���x�[�X
	/// </summary>
	BaseScene::Application();
}

void PlayScene::Initialize()
{
	/// <summary>
	/// �V�[���x�[�X
	/// </summary>
	BaseScene::Initialize();

	GameSpeed = GameNormalSpeed;

#pragma region 2D������
#pragma endregion 

#pragma region 3D������
	//�v���C���[
	player = make_unique<Player>();
	player->Initialize("Player");

	//�n��
	for(int i = 0; i < 6;i++){
		GroundPop({0, -150, 200 + (float)i*200});
	}
	//�A�E�g�G���A
	for(int i = 0; i < 6;i++){
		OutAreaPop({0, -150, 200 + (float)i*200});
	}

	//�V��
	skyDome = make_unique<SkyDome>();
	skyDome->Initialize("skydome");
#pragma endregion

#pragma region �ėp�@�\������
	hitStop = make_unique<HitStop>();
#pragma endregion
}

void PlayScene::Update()
{
	/// <summary>
	/// �V�[���x�[�X
	/// </summary>
	BaseScene::Update();

	if(frame % 60 == 0) second += 1;
	//�R�C��
	CoinPopCommands();

#pragma region ���͏���

	if(input->Trigger(DIK_1)){
		CoinPopReSet();
	}
	else if(input->Trigger(DIK_2)){
		Wall01Pop({0,-150,1000});
	}
	else if(input->Trigger(DIK_3)){
		hitStop->SetStopFrame(3.f);
		hitStop->HitStopStart();
	}
	else if(input->Trigger(DIK_4)){
		camera->ShakeStart();
	}
	else if(input->Trigger(DIK_5)){
		//hp->FadeStart();
		//hp->BreakStart();
	}

#pragma endregion

	//�q�b�g�X�g�b�v
	if(hitStop->Update(camera)) return;

#pragma region 2D�X�V
	//�X�R�A
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

#pragma endregion

#pragma region 3D�X�V
	//�v���C���[
	player->Update(camera, input);

	//�R�C��
	coin.remove_if([](unique_ptr<Coins>& obj){
		return obj->GetIsDead();
	});
	for(unique_ptr<Coins>& obj : coin){
		obj->Update(camera);
		obj->SetDepthSp(GameSpeed);
	}

	//�n��
	for(unique_ptr<Grounds>& obj : ground){
		obj->Update(camera);
		obj->SetDepthSp(GameSpeed);
	}
	//�A�E�g�G���A
	for(unique_ptr<OutArea>& obj : outArea){
		obj->Update(camera);
		obj->SetDepthSp(GameSpeed);
	}

	//�V��
	skyDome->Update(camera);

	//��01
	wall01.remove_if([](unique_ptr<Wall01>& obj){
		return obj->GetIsDead();
	});
	for(unique_ptr<Wall01>& obj : wall01){
		obj->Update(camera, hitStop.get());
		obj->SetDepthSp(GameSpeed);
	}

#pragma endregion

#pragma region �ėp�@�\�X�V
	//�Փ˔��胊�X�g�ǉ�
	collisionManager->SetCollision(player.get());
	for(const std::unique_ptr<Coins>& obj : coin)
	{
		collisionManager->SetCollision(obj.get());
	}
	for(const std::unique_ptr<Wall01>& obj : wall01)
	{
		collisionManager->SetCollision(obj.get());
	}
#pragma endregion

	/// <summary>
	/// �V�[���x�[�X
	/// </summary>
	BaseScene::EndUpdate();
}

void PlayScene::Draw()
{
	/// <summary>
	/// �V�[���x�[�X
	/// </summary>
	BaseScene::Draw();

#pragma region 2D�w�i
#pragma endregion

#pragma region 3D�`��
	//�v���C���[
	player->Draw_3D();

	//�R�C��
	for(unique_ptr<Coins>& obj : coin){
		obj->Draw();
	}

	//�n��
	for(unique_ptr<Grounds>& obj : ground){
		obj->Draw();
	}
	//�A�E�g�G���A
	for(unique_ptr<OutArea>& obj : outArea){
		obj->Draw();
	}

	//�V��
	skyDome->Draw();

	//��01
	for(unique_ptr<Wall01>& obj : wall01){
		obj->Draw();
	}

#pragma endregion

#pragma region 2D�`��UI
	Sprite::SetPipelineState();
	//�X�R�A
	for(unique_ptr<ScoreSprite>& sp : score){
		sp->Draw();
	}

	//�v���C���[
	player->Draw_2D();
	
#pragma endregion 

#ifdef _DEBUG
	debugText->Printf(0,0,1.f,"Camera:Eye	 X:%f Y:%f Z:%f", camera->GetEye().x,camera->GetEye().y,camera->GetEye().z);
	debugText->Printf(0,16,1.f,"Camera:Target X:%f Y:%f Z:%f", camera->GetTarget().x,camera->GetTarget().y,camera->GetTarget().z);

	debugText->Printf(0, 90, 1.f,"frame:%d, second:%d", frame, second);
	debugText->Printf(0, 106, 1.f, "coinNum : %d", coin.size());
	debugText->Printf(0, 122, 1.f, "scoreSpNum : %d", score.size());
	debugText->Printf(0, 138, 1.f, "wall01Num : %d", wall01.size());

	//�v���C���[
	debugText->Printf(0, 600, 1.f, "Player:Pos X:%f Y:%f Z:%f", player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
	debugText->Printf(0, 616, 1.f, "Player:Rot X:%f Y:%f Z:%f", XMConvertToRadians(player->GetRotation().x), XMConvertToRadians(player->GetRotation().y), XMConvertToRadians(player->GetRotation().z));
	debugText->Printf(0, 632, 1.f, "PlayerGetCoin : %d", player->GetCoinCount());
	debugText->Printf(0, 648, 1.f, "PlayerGetSore : %d", player->GetScoreCount());
	debugText->Printf(0, 664, 1.f, "PlayerHp : %d", player->GetHp());

#endif // _DEBUG

	/// <summary>
	/// �V�[���x�[�X
	/// </summary>
	BaseScene::EndDraw();
}

void PlayScene::Finalize()
{
	/// <summary>
	/// �V�[���x�[�X
	/// </summary>
	BaseScene::Finalize();

#pragma region 3D�㏈��
	//�v���C���[
	player->Finalize();

	//�R�C��
	for(unique_ptr<Coins>& obj : coin){
		obj->Finalize();
	}

	//�n��
	for(unique_ptr<Grounds>& obj : ground){
		obj->Finalize();
	}
	//�A�E�g�G���A
	for(unique_ptr<OutArea>& obj : outArea){
		obj->Finalize();
	}

	//�V��
	skyDome->Finalize();

	//��01
	for(unique_ptr<Wall01>& obj : wall01){
		obj->Finalize();
	}

#pragma endregion

#pragma region 2D�㏈��
	//�X�R�A
	for(unique_ptr<ScoreSprite>& sp : score){
		sp->Finalize();
	}	
#pragma endregion 
}

#pragma region �R�C������
void PlayScene::LoadCoinPopData()
{
	//file�J��
	ifstream file;
	file.open("Resources/csv/sample01.csv");
	assert(file.is_open());

	//file�|�{�𕶎���X�g���[���ɃR�s�[
	coinPopCommands << file.rdbuf();
	file.close();
}
void PlayScene::CoinPopCommands()
{
	//�ҋ@����
	if(IsWait){
		waitTime--;
		if(waitTime <= 0){
			//�ҋ@����
			IsWait = false;
		}
		return;
	}

	//��s���̕����������ϐ�
	string line;

	//�R�}���h���[�v
	while(getline(coinPopCommands, line)){
		//��s���̂���������X�g���[���ɕϊ����ĉ�͂��₷��
		istringstream line_stream(line);

		string word;
		//��؂�ōs�̑K��������擾
		getline(line_stream, word, ',');

		//"//"����n�܂�̂�comment
		if(word.find("//") == 0){
			//��΂�
			continue;
		}

		//POP�R�}���h
		if(word.find("POP") == 0){
			//X���W
			getline(line_stream, word, ',');
			float x = (float)atof(word.c_str());

			//Y���W
			getline(line_stream, word, ',');
			float y = (float)atof(word.c_str());

			//Z���W
			getline(line_stream, word, ',');
			float z = (float)atof(word.c_str());

			//POP
			CoinPop(Vector3(x,y,z));
		}
		else if(word.find("WAIT") == 0){
			getline(line_stream,word, ',');

			//�҂�����
			int32_t waitTime = atoi(word.c_str());

			//�ҋ@�J�n
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

