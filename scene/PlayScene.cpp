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

#pragma region 2D������
#pragma endregion 

#pragma region 3D������
	//�v���C���[
	player = make_unique<Player>();
	player->Initialize("player");

	//�R�C��
	LoadCoinPopData();

	//�n��
	for(int i = 0; i < 6;i++){
		GroundPop({0, -150, 200 + (float)i*200});
	}
#pragma endregion

#pragma region �ėp�@�\������
#pragma endregion
}

void PlayScene::Update()
{
	/// <summary>
	/// �V�[���x�[�X
	/// </summary>
	BaseScene::Update();
	frame += 1;

#pragma region ���͏���
#pragma endregion

#pragma region 2D�X�V
#pragma endregion

#pragma region 3D�X�V
	//�v���C���[
	player->Update(camera, input);

	//�R�C��
	UpdateCoinPopCommands();
	coin.remove_if([](unique_ptr<Coins>& obj){
		return obj->GetIsDead();
	});
	for(unique_ptr<Coins>& obj : coin){
		obj->Update(camera);
	}

	//�n��
	for(unique_ptr<Grounds>& obj : ground){
		obj->Update(camera);
	}
#pragma endregion

#pragma region �ėp�@�\�X�V
	//�Փ˔��胊�X�g�ǉ�
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
	player->Draw();

	//�R�C��
	for(unique_ptr<Coins>& obj : coin){
		obj->Draw();
	}

	//�n��
	for(unique_ptr<Grounds>& obj : ground){
		obj->Draw();
	}
#pragma endregion

#pragma region 2D�`��UI
	Sprite::SetPipelineState();
#pragma endregion 

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

#pragma endregion

#pragma region 2D�㏈��

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
void PlayScene::UpdateCoinPopCommands()
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
