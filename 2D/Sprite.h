#pragma once
#include <d3d12.h>
#include <d3dx12.h>
#include <wrl.h>
#include <DirectXMath.h>

#include"TextureManager.h"
#include "Vector2.h"
#include "Vector3.h"

/// <summary>
/// �X�v���C�g
/// </summary>
class Sprite
{
public://�G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMFLOAT4 = DirectX::XMFLOAT4;

public://�T�u�N���X
	class Common{
		friend class Sprite;
		friend class PostEffect;

	private:
		//���_��
		const int vertNum = 4;
		//DirectXCommon
		DirectXCommon* dxCommon = nullptr;
		//�p�C�v���C���X�e�[�g�I�u�W�F�N�g
		ComPtr<ID3D12PipelineState> pipelinestate;
		//���[�g�V�O�l�`��
		ComPtr<ID3D12RootSignature> rootsignature;
		//�ˉe�s��
		XMMATRIX matProjection{};


		//�e�N�X�`���}�l�[�W���[
		//TextureManager* textureManager = nullptr;

	public:
		void InitializeGraphicsPipeline(const std::string& directoryPath);
	};

	//�X�v���C�g�f�[�^�\��
	struct VertexPosUv
	{
		Vector3 pos;
		Vector2 uv;
	};

	//�萔�o�b�t�@�p�f�[�^�\����(3D�ϊ��s��
	struct ConstBufferData{
		XMMATRIX mat;	//3D�ϊ��s��
		XMFLOAT4 color;	//�F(RGBA)
	};

public://�ÓI�����o�֐�
	/// <summary>
	/// �ÓI�����o�̏�����
	/// </summary>
	static void StaticInitialize(DirectXCommon* dxCommon,
		int window_width, int window_height, const std::string& directoryPath = "Resources/shader");

	/// <summary>
	/// �ÓI�����o�̉��
	/// </summary>
	static void StaticFinalize();

	/// <summary>
	/// �O���t�B�b�N�X�p�C�v���C���̃Z�b�g
	/// </summary>
	/// <param name="commandList">�R�}���h���X�g</param>
	static void SetPipelineState();


	static Sprite* Create(UINT texNumber, Vector2 pos, XMFLOAT4 color = {1,1,1,1},
		Vector2 anchorpoint = {0.f,0.f}, bool isFlipX = false, bool isFlipY = false);

protected://�ÓI�����o�ϐ�
	static Common* common;


public://�����o�֐�

	Sprite();
	Sprite(UINT texnumber, Vector3 pos, Vector2 size, XMFLOAT4 color, Vector2 anchorpoint, bool isFlipX, bool isFlipY);

	/// <summary>
	/// ������
	/// </summary>
	bool Initialize(UINT texNumber);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	//�X�v���C�g�P�̒��_�o�b�t�@�̓]��
	void SpriteTransferVertexBuffer();


	/// <summary>
	/// ���W�擾
	/// </summary>
	Vector3 GetPosition()	{return position;}

	/// <summary>
	/// ���W�ݒ�
	/// </summary>
	void SetPosition(Vector2 pos);

	/// <summary>
	/// �T�C�Y�擾
	/// </summary>
	Vector2 GetSize()	{return size;}

	/// <summary>
	/// �T�C�Y�ݒ�
	/// </summary>
	void SetSize(Vector2 size);

	/// <summary>
	/// �A���J�[�|�C���g�ݒ�
	/// </summary>
	void SetAnchorpoint(Vector2 pos);

	/// <summary>
	/// �؂蔲���T�C�Y�ݒ�
	/// </summary>
	/// <param name="tex_x">����X</param>
	/// <param name="tex_y">����Y</param>
	/// <param name="tex_width">��</param>
	/// <param name="tex_height">����</param>
	void SetTextureRect(float tex_x, float tex_y, float tex_width, float tex_height);

	/// <summary>
	/// ���E���]�ݒ�
	/// </summary>
	void SetIsFlipX(bool IsFlipX);

	/// <summary>
	/// �㉺���]�ݒ�
	/// </summary>
	void SetIsFlipY(bool IsFlipY);

	/// <summary>
	/// �F�ݒ�
	/// </summary>
	void SetColor(XMFLOAT4 color);

	/// <summary>
	/// ��\��
	/// </summary>
	void SetIsInvisible(bool IsInvisible);

protected://�����o�ϐ�
	///���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffData;
	//���_�o�b�t�@�}�b�v
	VertexPosUv* vertMap = nullptr;
	//�萔�o�b�t�@�}�b�v
	ConstBufferData* constMap = nullptr;
	///���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	//�e�N�X�`���ԍ�
	UINT texNumber = 0;

	//���W
	Vector3 position = {0, 0, 0};
	//Z������̉�]�p
	float rotation = 0.f;
	//�傫��
	Vector2 size = {100, 100};

	//�A���J�[�|�C���g
	Vector2 anchorpoint = {0.0f, 0.0f};
	//���E���]
	bool IsFlipX = false;
	//�㉺���]
	bool IsFlipY = false;
	//�e�N�X�`��������W
	Vector2 texLeftTop = {0,0};
	//�e�N�X�`���؂�o���T�C�Y
	Vector2 texSize = {100, 100};
	//��\��
	bool IsInvisible = false;

	//���[���h�s��
	XMMATRIX matWorld;

	//�F
	XMFLOAT4 color = {1, 1, 1, 1};

	//���\�[�X���
	D3D12_RESOURCE_DESC resourceDesc;
};

