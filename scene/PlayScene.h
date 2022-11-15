#pragma once
#include <list>
#include <sstream>

#include "BaseScene.h"

#include "Sprite.h"
#include "FbxModelManager.h"
#include "FbxModelObject.h"
#include "WorldTransform.h"

#include "3D/Player/Player.h"
#include "3D/Coins/Coins.h"
#include "3D/Grounds/Grounds.h"
#include "3D/OutArea/OutArea.h"
#include "3D/SkyDome/SkyDome.h"
#include "3D/Wall01/Wall01.h"
#include "3D/Wall02/Wall02.h"

#include "2D/Score/ScoreSprite.h"
#include "2D/ScoreText/ScoreText.h"

#include "System/HitStop.h"



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

	//�n��POP
	void GroundPop(Vector3 position);
	//�A�E�g�G���APOP
	void OutAreaPop(Vector3 position);

	//��
	void Wall01Pop(Vector3 position);
	void Wall02Pop(Vector3 position);

	//�X�R�APOP
	void ScoreUp100Pop();
	void ScoreDown100Pop();

private:
	//�v���C���[
	std::unique_ptr<Player> player;

	//�R�C��
	std::list<std::unique_ptr<Coins>> coin;
	std::stringstream coinPopCommands;
	int waitTime = 0;
	bool IsWait = false;

	//�n��
	std::list<std::unique_ptr<Grounds>> ground;
	std::list<std::unique_ptr<OutArea>> outArea;

	//�V��
	std::unique_ptr<SkyDome> skyDome;

	//��
	std::list<std::unique_ptr<Wall01>> wall01;
	std::list<std::unique_ptr<Wall02>> wall02;

	//�X�R�A
	std::list<std::unique_ptr<ScoreSprite>> score;
	//�X�R�A�\
	//std::unique_ptr<ScoreText> scoreText;

	//�Q�[���i�s���x
	float GameSpeed = 0.f;
	const float GameNormalSpeed = 6.f;
	const float GameAcceleratorSpeed = 18.f;

	int frame = 0;
	int second = 0;

	//�q�b�g�X�g�b�v
	std::unique_ptr<HitStop> hitStop;
};

