#pragma once

#include <string>
#include <DirectXMath.h>
#include <vector>
#include <DirectXTex.h>
#include <Window.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>

#include "Vector2.h"
#include "Vector3.h"

#include <fbxsdk.h>

struct Node
{
	//���O
	std::string name;
	//���[�J���X�P�[��
	DirectX::XMVECTOR scaling = {1, 1, 1, 0};
	//���[�J����]�p
	DirectX::XMVECTOR rotation = {0,0, 0, 0};
	//���[�J���ړ�
	DirectX::XMVECTOR translation = {0, 0, 0, 1};
	//���[�J���ό`�s��
	DirectX::XMMATRIX transform;
	//�O���[�o���ό`�s��
	DirectX::XMMATRIX globalTransform;
	//�e�m�[�h
	Node* parent = nullptr;
};


//�{�[���\����
struct Bone
{
	//���O
	std::string name;
	//�����p���̋t�s��
	DirectX::XMMATRIX invInitialPose;
	//�N���X�^�[(FBX���̃{�[�����)
	FbxCluster* fbxCluster;
	//�R���X�g���N�^
	Bone(const std::string& name)
	{
		this->name = name;
	}
};


class FbxModelManager{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	template <class T> using vector = std::vector<T>;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using TexMetadata = DirectX::TexMetadata;
	using ScratchImage = DirectX::ScratchImage;
	using string = std::string;

public:
	static const int MAX_BONE_INDICES = 4;

public:
	friend class FbxLoader;
public:
	//���_�f�[�^
	struct VertexPosNormalUvSkin{
		Vector3 pos;
		Vector3 normal;
		Vector2 uv;
		UINT boneIndex[MAX_BONE_INDICES];
		float boneWeight[MAX_BONE_INDICES];
	};

public:

	~FbxModelManager();

	//�o�b�t�@����
	void CreateBuffer(ID3D12Device* device);

	//�`��
	void Draw(ID3D12GraphicsCommandList* commandList);

	const XMMATRIX& GetModelTransform() {return meshNode->globalTransform;}

	//Getter
	vector<Bone>& GetBones()	{return bones;}
	FbxScene* GetFbxScene()	{return fbxScene;}

private:
	string name;
	vector<Node> nodes;
	vector<Bone> bones;

	FbxScene* fbxScene = nullptr;

	//���b�V�������m�[�h
	Node* meshNode = nullptr;
	//���_�f�[�^�z��
	vector<VertexPosNormalUvSkin> vertices;
	//���_�C���f�b�N�X
	vector<unsigned short> indices;

	ComPtr<ID3D12Resource> vertBuffer;
	ComPtr<ID3D12Resource> indexBuffer;
	ComPtr<ID3D12Resource> texBuffer;

	VertexPosNormalUvSkin* vertMap = nullptr;
	unsigned short* indexMap = nullptr;

	D3D12_VERTEX_BUFFER_VIEW vbView{};
	D3D12_INDEX_BUFFER_VIEW ibView{};

	ComPtr<ID3D12DescriptorHeap> descriptorHeapSRV;


	Vector3 ambient = {1,1,1};
	Vector3 diffuse = {1,1,1};
	TexMetadata metaData = {};
	ScratchImage scratchImage = {};
};