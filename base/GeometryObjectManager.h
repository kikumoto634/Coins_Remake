#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>


#include "Vector2.h"
#include "Vector3.h"

class GeometryObjectManager
{
public://�G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:	//�萔
	//�e�N�X�`���̍ő喇��
	static const int maxObjectCount = 512;

public:
	struct VertexPosNormalUv
	{
		Vector3 pos;
		Vector3 normal;
		Vector2 uv;
	};

public:
	static GeometryObjectManager* GetInstance();

public:
	/// <summary>
	/// �o�b�t�@����
	/// </summary>
	void CreateBuffer();

	//Get
	
	int GetMaxObjectCount()	{return maxObjectCount;}
	
	//�C���f�b�N�X
	uint16_t GetIndices()	{return _countof(indices);}

	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW GetvbView()	{return vbView;}
	//�C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW GetibView()		{return ibView;}


private:
	//���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuffer;
	//�C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuffer;

	//���_�}�b�v
	VertexPosNormalUv* vertMap = nullptr;
	//�C���f�b�N�X�}�b�v
	uint16_t* indexMap = nullptr;

	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView{};

	//���_�f�[�^
	VertexPosNormalUv vertices[24];
	//�C���f�b�N�X�f�[�^
	uint16_t indices[36];
};

