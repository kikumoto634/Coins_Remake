#pragma once

#include "DirectXCommon.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <wrl.h>
#include "DirectXTex.h"

using namespace DirectX;

//�e�N�X�`���}�l�[�W���[
class TextureManager
{
public://�G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:	//�萔
	//�e�N�X�`���̍ő喇��
	static const int maxTextureCount = 512;

	//�f�B���N�g���p�X
	const std::string directoryPath = "Resources/";

public:
	/// <summary>
	/// �e�N�X�`��
	/// </summary>
	struct Texture {
		// �e�N�X�`�����\�[�X
		ComPtr<ID3D12Resource> resource;
		// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
		CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
		// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
		CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	};

public://�ÓI

	static void Load(UINT texnumber, const std::string& filename);

	static TextureManager* GetInstance();

public:	//�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="dxCommon">DirectXCommon->device.Get()</param>
	void Initialize(DirectXCommon* dxCommon);

	/// <summary>
	/// �N���A
	/// </summary>
	void ResetAll();

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <param name="texnumber">�e�N�X�`���ԍ�</param>
	/// <param name="filename">�e�N�X�`���t�@�C����</param>
	void LoadTexture(UINT texnumber, const std::string& filename);

	/// <summary>
	/// �e�N�X�`���o�b�t�@�擾
	/// </summary>
	/// <param name="texnumber">�e�N�X�`���ԍ�</param>
	/// <returns></returns>
	ID3D12Resource* GetSpriteTexBuffer(UINT texnumber);

	/// <summary>
	/// �f�X�N���v�^�q�[�v���Z�b�g
	/// </summary>
	/// <param name="commandList">�O���t�B�b�N�X�R�}���h</param>
	void SetDescriptorHeaps (ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// SRV���Z�b�g
	/// </summary>
	/// <param name="commandList">�O���t�B�b�N�X�R�}���h</param>
	/// <param name="RootParameterIndex">���[�g�p�����[�^�ԍ�</param>
	/// <param name="texnumber">�e�N�X�`���ԍ�</param>
	void SetShaderResourceView(ID3D12GraphicsCommandList* commandList, UINT RootParameterIndex, UINT texnumber);

	/// <summary>
	/// �f�X�N���v�^�q�[�v�擾
	/// </summary>
	/// <returns></returns>
	ID3D12DescriptorHeap* GetDescHeap() {return descHeap.Get(); }

private:	//�����o�ϐ�
	//�e�N�X�`���p�f�X�N���v�^�q�[�v�̐���
	ComPtr<ID3D12DescriptorHeap> descHeap;
	//�e�N�X�`�����z��
	Texture textures[maxTextureCount];
	//�f�X�N���v�^�T�C�Y
	UINT descriptorhandleIncrementSize = 0u;
	//DirectXCommon
	DirectXCommon* dxCommon = nullptr;
};

