#pragma once

#include <Window.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>

#include "FbxModelManager.h"
#include "FbxLoader.h"
#include "Camera.h"
#include "Vector2.h"
#include "Vector3.h"
#include "WorldTransform.h"
#include "DirectXCommon.h"

class FbxModelObject{
protected:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	static const int MAX_BONES = 32;

public:
	class CommonFbx{
		friend class FbxModelObject;

	public:
		void InitializeGraphicsPipeline();

	private:
		DirectXCommon* dxCommon = nullptr;

		ComPtr<ID3D12RootSignature> rootSignature;
		ComPtr<ID3D12PipelineState> pipelineState;
	};

	struct ConstBufferDataTransform{
		XMMATRIX viewproj;
		XMMATRIX world;
		XMMATRIX shadow;
		Vector3 cameraPos;
	};

	//�萔�o�b�t�@�p�f�[�^�\����(�X�L�j���O)
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};

public:
	static void StaticInitialize(DirectXCommon* dxCommon);
	static void StaticFinalize();

	static FbxModelObject* Create(FbxModelManager* model);

private:
	static CommonFbx* common;

public:
	FbxModelObject();
	FbxModelObject(FbxModelManager* model);

	bool Initialize();
	void Update(WorldTransform worldTransform, Camera* camera);
	void Draw();

	/// <summary>
	/// �A�j���[�V�����J�n
	/// </summary>
	void PlayAnimation();

protected:
	DirectX::XMFLOAT3 paralleLightVec = {1,-1,1};

	ComPtr<ID3D12Resource> constBufferTransform;
	//�萔�o�b�t�@(�X�L��)
	ComPtr<ID3D12Resource> constBufferSkin;

	ConstBufferDataTransform* constMap = nullptr;
	ConstBufferDataSkin* constSkinMap = nullptr;

	FbxModelManager* model = nullptr;

	//1frame�̎���
	FbxTime frameTime;
	//�A�j���[�V�����J�n����
	FbxTime startTime;
	//�A�j���[�V�����I������
	FbxTime endTime;
	//���ݎ���(�A�j���[�V����)
	FbxTime currentTime;
	//�A�j���[�V�����Đ���
	bool isPlay = false;
};