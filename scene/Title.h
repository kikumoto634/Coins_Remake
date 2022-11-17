#pragma once
#include "BaseScene.h"

#include "3D/Player/Player.h"
#include "3D/Grounds/Grounds.h"
#include "3D/OutArea/OutArea.h"
#include "3D/SkyDome/SkyDome.h"

class Title : public BaseScene
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Title(DirectXCommon* dxCommon, Window* window);

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
	//�n��POP
	void GroundPop(Vector3 position);
	//�A�E�g�G���APOP
	void OutAreaPop(Vector3 position);

	void TitleLogoMove();

private:
	float GameSpeed = 6.f;

	//�v���C���[
	std::unique_ptr<Player> playerObj;

	//�V��
	std::unique_ptr<SkyDome> skyDome;

	//�n��
	std::list<std::unique_ptr<Grounds>> ground;
	std::list<std::unique_ptr<OutArea>> outArea;

	//�^�C�g�����S
	std::unique_ptr<BaseSprite> titleLogo;
	const Vector2 LogoStartPos = {600, 30};
	const Vector2 LogoEndPos = {600, 80};
	Vector2 LogoPos = LogoStartPos;
	Vector2 LogoSize = {600,300};
	float LogoTime = 0.f;

#ifdef _DEBUG
	Vector3 target;
	Vector3 eye;
#endif // _DEBUG

};

