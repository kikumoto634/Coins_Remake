#pragma once
#include <list>
#include <sstream>

#include "BaseScene.h"

#include "Sprite.h"
#include "FbxModelManager.h"
#include "FbxModelObject.h"
#include "WorldTransform.h"

#include "Player\Player.h"
#include "Coins/Coins.h"
#include "Grounds/Grounds.h"



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
	void UpdateCoinPopCommands();
	void CoinPop(Vector3 pos);


	void GroundPop(Vector3 position);


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

	int frame = 0;
};

