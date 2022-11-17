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
	//�X�R�A�\
	scoreText = make_unique<ScoreText>();
	scoreText->Initialize(1);
	//�X�R�A�{�[�h
	scoreBoard = make_unique<ScoreBoard>();
	scoreBoard->Initialize(5);
	//�X�R�A�Q�[�W
	scoreGage = make_unique<ScoreGage>();
	scoreGage->Initialize(6);
#pragma endregion 

#pragma region 3D������
	//�v���C���[
	player = make_unique<Player>();
	player->Initialize("Player");

	//�n��
	for(int i = 0; i < 1;i++){
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
	//�q�b�g�X�g�b�v
	hitStop = make_unique<HitStop>();
#pragma endregion

	//���U���g
	result = make_unique<Result>();
	result->Initialize(8);
}

void PlayScene::Update()
{
	/// <summary>
	/// �V�[���x�[�X
	/// </summary>
	BaseScene::Update();

	//���U���g
	result->Update(player->GetIsDead());

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

	//�q�b�g�X�g�b�v
	if(hitStop->Update(camera)) return;
	//����
	GameSpeed = GameNormalSpeed;
	if(player->GetIsAccelerator()){
		GameSpeed = GameAcceleratorSpeed;
	}

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
	//�X�R�A�\
	scoreText->Printf(578, 24, 1.5f, "High Score");
	scoreText->Printf(585, 48, 1.5f, "%09d", player->GetScoreCount());
	//�X�R�A�{�[�h
	scoreBoard->Update();
	//�X�R�A�Q�[�W
	scoreGage->Update();
#pragma endregion

#pragma region 3D�X�V
	//�v���C���[
	player->Update(camera, input);
	if(player->GetIsDead()){
		GameSpeed *= player->GetDeadAnimSp();
	}

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
	}
	//�A�E�g�G���A
	for(unique_ptr<OutArea>& obj : outArea){
		obj->Update(camera);
		obj->SetDepthSp(GameSpeed);
	}

	//�V��
	skyDome->Update(camera);

	//��
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

#pragma region �ėp�@�\�X�V
	//�Փ˔��胊�X�g�ǉ�
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

	//��
	for(unique_ptr<Wall01>& obj : wall01){
		obj->Draw();
	}
	for(unique_ptr<Wall02>& obj : wall02){
		obj->Draw();
	}

#pragma endregion

#pragma region 2D�`��UI
	Sprite::SetPipelineState();
	//�X�R�A
	for(unique_ptr<ScoreSprite>& sp : score){
		sp->Draw();
	}

	if(!player->GetIsDead()){
		//�X�R�A�{�[�h
		scoreBoard->Draw();
		//�X�R�A�\
		scoreText->DrawAll();
	}
	//�X�R�A�Q�[�W
	scoreGage->Draw();

	//�v���C���[
	player->Draw_2D();
	
#pragma endregion 

	//���U���g
	result->Draw();

#ifdef _DEBUG
	debugText->Printf(0,0,1.f,"Camera:Eye	 X:%f Y:%f Z:%f", camera->GetEye().x,camera->GetEye().y,camera->GetEye().z);
	debugText->Printf(0,16,1.f,"Camera:Target X:%f Y:%f Z:%f", camera->GetTarget().x,camera->GetTarget().y,camera->GetTarget().z);

	debugText->Printf(0, 90, 1.f,"frame:%d, second:%d", frame, second);
	debugText->Printf(0, 106, 1.f, "coinNum : %d", coin.size());
	debugText->Printf(0, 122, 1.f, "scoreSpNum : %d", score.size());
	debugText->Printf(0, 138, 1.f, "wall01Num : %d", wall01.size());
	debugText->Printf(0, 154, 1.f, "wall02Num : %d", wall02.size());

	//�v���C���[
	debugText->Printf(0, 600, 1.f, "Player:Pos X:%f Y:%f Z:%f", player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
	debugText->Printf(0, 616, 1.f, "Player:Rot X:%f Y:%f Z:%f", XMConvertToRadians(player->GetRotation().x), XMConvertToRadians(player->GetRotation().y), XMConvertToRadians(player->GetRotation().z));
	debugText->Printf(0, 632, 1.f, "PlayerGetCoin : %d", player->GetCoinCount());
	debugText->Printf(0, 648, 1.f, "PlayerGetSore : %d", player->GetScoreCount());
	debugText->Printf(0, 664, 1.f, "PlayerHp : %d", player->GetHp());
	debugText->Printf(0, 680, 1.f, "PlayerIsAccelerator : %d", player->GetIsAccelerator());
	debugText->Printf(0, 696, 1.f, "PlayerIsAcceleratorGage : %f", player->GetAcceleratorGage());

	//�f�o�b�N�{�^��
	debugText->Print("DIK_1 : Coin Appearance",1000,0,1.f);
	debugText->Print("DIK_2 : Wall1 Appearance",1000,16,1.f);
	debugText->Print("DIK_3 : Wall2 Appearance",1000,32,1.f);
	debugText->Print("DIK_4 : HitStop",1000,48,1.f);
	debugText->Print("DIK_5 : CameraShake(Unimplemented)",1000,64,1.f);
	debugText->Print("DIK_6 : PlayerDead",1000,80,1.f);
	debugText->Print("DIK_7 : AcceleratorGage MAX",1000,96,1.f);

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

	//��0
	for(unique_ptr<Wall01>& obj : wall01){
		obj->Finalize();
	}
	for(unique_ptr<Wall02>& obj : wall02){
		obj->Finalize();
	}

#pragma endregion

#pragma region 2D�㏈��
	//�X�R�A
	for(unique_ptr<ScoreSprite>& sp : score){
		sp->Finalize();
	}	
	//�X�R�A�\
	scoreText->Finalize();
	//�X�R�A�{�[�h
	scoreBoard->Finalize();
	//�X�R�A�Q�[�W
	scoreGage->Finalize();
#pragma endregion 

	result->Finalize();
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

