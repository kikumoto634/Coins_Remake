#pragma once
#include <list>
#include <sstream>

#include "BaseScene.h"

#include "Sprite.h"
#include "FbxModelManager.h"
#include "FbxModelObject.h"
#include "WorldTransform.h"

#include "3D/Player\Player.h"
#include "3D/Coins/Coins.h"
#include "3D/Grounds/Grounds.h"
#include "3D/Wall01/Wall01.h"

#include "2D/Score/ScoreSprite.h"



class PlayScene : public BaseScene
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayScene(DirectXCommon* dxCommon, Window* window);

	/// <summary>
	/// �N����
	/// </summary>
	void Application() override;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// �㏈��
	/// </summary>
	void Finalize() override;

private:
	//�R�C��POP
	void LoadCoinPopData();
	void CoinPopCommands();
	void CoinPop(Vector3 pos);
	void CoinPopReSet();

	//�X�R�APOP
	void ScoreUp100Pop();
	void ScoreDown100Pop();

	//�n��POP
	void GroundPop(Vector3 position);

	//��01
	void Wall01Pop(Vector3 position);

private:
	//�v���C���[
	std::unique_ptr<Player> player;

	//�R�C��
	std::list<std::unique_ptr<Coins>> coin;
	std::stringstream coinPopCommands;
	int waitTime = 0;
	bool IsWait = false;

	//�X�R�A
	std::list<std::unique_ptr<ScoreSprite>> score;

	//�n��
	std::list<std::unique_ptr<Grounds>> ground;

	//��01
	std::list<std::unique_ptr<Wall01>> wall01;

	//�Q�[���i�s���x
	const float GameSpeed = 4.f;

	int frame = 0;
	int second = 0;
};

