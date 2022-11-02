#include "GeometryObjectManager.h"
#include <cassert>
#include "DirectXCommon.h"

using namespace std;
using namespace DirectX;

GeometryObjectManager *GeometryObjectManager::GetInstance()
{
	static GeometryObjectManager instance;
	return &instance;
}

void GeometryObjectManager::CreateBuffer()
{
	HRESULT result;
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

#pragma region �l�p�`���
	//���_�f�[�^
	VertexPosNormalUv vertices[] = {
		//�O
		{{-5.0f, -5.0f, -5.0f}, {}, {0.0f, 1.0f}},
		{{-5.0f, +5.0f, -5.0f}, {}, {0.0f, 0.0f}},
		{{+5.0f, -5.0f, -5.0f}, {}, {1.0f, 1.0f}},
		{{+5.0f, +5.0f, -5.0f}, {}, {1.0f, 0.0f}},
		//��
		{{-5.0f, -5.0f, +5.0f}, {}, {0.0f, 1.0f}},
		{{-5.0f, +5.0f, +5.0f}, {}, {0.0f, 0.0f}},
		{{+5.0f, -5.0f, +5.0f}, {}, {1.0f, 1.0f}},
		{{+5.0f, +5.0f, +5.0f}, {}, {1.0f, 0.0f}},
		//��
		{{-5.0f, -5.0f, -5.0f}, {}, {0.0f, 1.0f}},
		{{-5.0f, -5.0f, +5.0f}, {}, {0.0f, 0.0f}},
		{{-5.0f, +5.0f, -5.0f}, {}, {1.0f, 1.0f}},
		{{-5.0f, +5.0f, +5.0f}, {}, {1.0f, 0.0f}},
		//�E
		{{+5.0f, -5.0f, -5.0f}, {}, {0.0f, 1.0f}},
		{{+5.0f, -5.0f, +5.0f}, {}, {0.0f, 0.0f}},
		{{+5.0f, +5.0f, -5.0f}, {}, {1.0f, 1.0f}},
		{{+5.0f, +5.0f, +5.0f}, {}, {1.0f, 0.0f}},
		//��
		{{-5.0f, -5.0f, -5.0f}, {}, {0.0f, 1.0f}},
		{{+5.0f, -5.0f, -5.0f}, {}, {0.0f, 0.0f}},
		{{-5.0f, -5.0f, +5.0f}, {}, {1.0f, 1.0f}},
		{{+5.0f, -5.0f, +5.0f}, {}, {1.0f, 0.0f}},
		//��
		{{-5.0f, +5.0f, -5.0f}, {}, {0.0f, 1.0f}},
		{{+5.0f, +5.0f, -5.0f}, {}, {0.0f, 0.0f}},
		{{-5.0f, +5.0f, +5.0f}, {}, {1.0f, 1.0f}},
		{{+5.0f, +5.0f, +5.0f}, {}, {1.0f, 0.0f}},
	};
	for(int i = 0; i < _countof(vertices); i++){
		this->vertices[i] = vertices[i];
	}

	///�C���f�b�N�X�f�[�^
	uint16_t indices[] = {
		//�O
		0, 1, 2,
		2, 1, 3,
		//��
		5, 4, 6,
		5, 6, 7,
		//��
		8, 9, 10,
		10, 9, 11,
		//�E
		13, 12, 14,
		13, 14, 15,
		//��
		16, 17, 18,
		18, 17, 19,
		//��
		21, 20, 22,
		21, 22, 23,
	};
	for(int i = 0; i < _countof(indices); i++){
		this->indices[i] = indices[i];
	}

	///�@���v�Z
	for(int i = 0; i < _countof(indices)/3; i++){
		//�O�p�`�ɃC���f�b�N�X�����o���āA�ꎞ�I�ȕϐ�������
		uint16_t index0 = indices[i*3+0];
		uint16_t index1 = indices[i*3+1];
		uint16_t index2 = indices[i*3+2];
		//�O�p�`���\�����钸�_���W���x�N�g���ɑ��
		Vector3 p0 = vertices[index0].pos;
		Vector3 p1 = vertices[index1].pos;
		Vector3 p2 = vertices[index2].pos;
		//p0->p1�x�N�g���Ap0->p2�x�N�g���̌v�Z	(�x�N�g�����Z)
		Vector3 v1 = p0 - p1;
		Vector3 v2 = p0 - p2;
		//�O�ς͗������琂���ȃx�N�g��
		Vector3 normal = v1.cross(v2);
		//���K��(������1�ɂ���)
		normal = normal.normalize();
		//���߂��@���𒸓_�f�[�^�ɑ��
		vertices[index0].normal = normal;
		vertices[index1].normal = normal;
		vertices[index2].normal = normal;
	}
#pragma endregion

	//���_�o�b�t�@
	//�T�C�Y
	UINT sizeVB = static_cast<UINT>(sizeof(VertexPosNormalUv)*_countof(vertices));
	{
		//�q�[�v�v���p�e�B
		CD3DX12_HEAP_PROPERTIES heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		//���\�[�X�ݒ�
		CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeVB);
		//����
		result = dxCommon->GetDevice()->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&vertBuffer)
		);
		assert(SUCCEEDED(result));

		//�]��
		result = vertBuffer->Map(0, nullptr, (void**)&vertMap);
		if(SUCCEEDED(result)){
			memcpy(vertMap, vertices,sizeof(vertices));
			vertBuffer->Unmap(0,nullptr);
		}
	}

	//���_�o�b�t�@�r���[�̐���
	vbView.BufferLocation = vertBuffer->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(VertexPosNormalUv);

	//���_�C���f�b�N�X
	//�T�C�Y
	UINT sizeIB = static_cast<UINT>(sizeof(uint16_t)*_countof(indices));
	{
		//�q�[�v�v���p�e�B
		CD3DX12_HEAP_PROPERTIES heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		//���\�[�X�ݒ�
		CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeIB);
		//����
		result = dxCommon->GetDevice()->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&indexBuffer)
		);
		assert(SUCCEEDED(result));

		//�]��
		result = indexBuffer->Map(0, nullptr, (void**)&indexMap);
		if(SUCCEEDED(result)){
			memcpy(indexMap, indices,sizeof(indices));
			indexBuffer->Unmap(0,nullptr);
		}
	}

	//�C���f�b�N�X�o�b�t�@�r���[(IBV)�̍쐬
	ibView.BufferLocation = indexBuffer->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes= sizeIB;
}
