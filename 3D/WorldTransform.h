#pragma once
#include <DirectXMath.h>
#include <d3d12.h>
#include <wrl.h>

#include "Vector2.h"
#include "Vector3.h"

//�萔�o�b�t�@�p�f�[�^�\����
struct ConstBufferDataWorldTransform{
	DirectX::XMMATRIX matWorld;	//���[�J�� -> ���[���h�ϊ��s��
};

/// <summary>
/// ���[���h�ϊ��s��
/// </summary>
struct WorldTransform{
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffer;
	//�}�b�s���O�ς݃A�h���X
	ConstBufferDataWorldTransform* constMap = nullptr;

	//���[�J���X�P�[��
	Vector3 scale = {1,1,1};
	//���[�J����]�p
	Vector3 rotation = {0,0,0};
	//���[�J�����W
	Vector3 translation = {0,0,0};
	//���[�J�� -> ���[���h�ϊ��s��
	DirectX::XMMATRIX matWorld;
	//�e
	WorldTransform* parent = nullptr;


	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �萔�o�b�t�@����
	/// </summary>
	void CreateConstBuffer();

	/// <summary>
	/// �}�b�s���O
	/// </summary>
	void Map();

	/// <summary>
	/// �s��̍X�V
	/// </summary>
	void UpdateMatrix();
};

