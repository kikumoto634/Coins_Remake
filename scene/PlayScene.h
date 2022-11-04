#pragma once
#include "BaseScene.h"

#include "Sprite.h"
#include "FbxModelManager.h"
#include "FbxModelObject.h"
#include "WorldTransform.h"

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

	//�v���C���[
	FbxModelManager* playerModel;
	FbxModelObject* playerObject;
	WorldTransform playerWorld;

	//�n��
	FbxModelManager* groundModel;
	FbxModelObject* groundObject[10];
	WorldTransform groundWorld[10];

	//�J����
	Vector3 eye{};
	Vector3 target{};
};

