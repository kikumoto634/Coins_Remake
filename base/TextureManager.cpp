#include "TextureManager.h"
#include <assert.h>

void TextureManager::Load(UINT texnumber, const std::string &filename)
{
	TextureManager::GetInstance()->LoadTexture(texnumber, filename);
}

TextureManager *TextureManager::GetInstance()
{
	static TextureManager instance;
	return &instance;
}

void TextureManager::Initialize(DirectXCommon* dxCommon)
{
	//�����o�֐��ɋL�^
	this->dxCommon = dxCommon;

	descriptorhandleIncrementSize = dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//�e�N�X�`�����Z�b�g
	ResetAll();
}

void TextureManager::ResetAll()
{
	HRESULT result;

	//�f�X�N���v�^�q�[�v�̐���
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc= {};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	descHeapDesc.NumDescriptors= maxTextureCount;
	result = this->dxCommon->GetDevice()->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap));
	assert(SUCCEEDED(result));

	//�S�e�N�X�`��������
	for(size_t i = 0; i < maxTextureCount; i++){
		textures[i].resource.Reset();
		textures[i].cpuDescHandleSRV.ptr = 0;
		textures[i].gpuDescHandleSRV.ptr = 0;
	}
}

void TextureManager::LoadTexture(UINT texnumber, const std::string& filename)
{
	//�ُ�Ȕԍ��̎w������o
	assert(texnumber <= maxTextureCount - 1);

	HRESULT result;

	//�t���p�X
	std::string fullPath = directoryPath + filename;
	//���j�R�[�h������ɕϊ�
	wchar_t wfilePath[256];
	MultiByteToWideChar(CP_ACP, 0, fullPath.c_str(), -1, wfilePath, _countof(wfilePath));

	///�摜�t�@�C���̗p��
	TexMetadata metadata{};
	ScratchImage scratchImg{};
	//WIC�e�N�X�`���f�[�^�̃��[�h
	result = LoadFromWICFile(
		wfilePath,
		WIC_FLAGS_NONE,
		&metadata, scratchImg);
	assert(SUCCEEDED(result));


	//�~�b�v�}�b�v�̐���
	ScratchImage mipChain{};
	//����
	result = GenerateMipMaps(
		scratchImg.GetImages(), 
		scratchImg.GetImageCount(), 
		scratchImg.GetMetadata(),
		TEX_FILTER_DEFAULT, 
		0, 
		mipChain
	);
	if(SUCCEEDED(result))
	{
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}

	//�t�H�[�}�b�g������������
	//�ǂݍ��񂾃f�B�t���[�Y�e�N�X�`����SRGB�Ƃ��Ĉ���
	metadata.format = MakeSRGB(metadata.format);

	///�e�N�X�`���o�b�t�@�ݒ�
	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES textureHandleProp{};
	textureHandleProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	textureHandleProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	textureHandleProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	//���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC textureResourceDesc = CD3DX12_RESOURCE_DESC::Tex2D
		(
			metadata.format,
			metadata.width,
			(UINT)metadata.height,
			(UINT16)metadata.arraySize,
			(UINT16)metadata.mipLevels
		);

	//�e�N�X�`���o�b�t�@�̐���
	result= dxCommon->GetDevice()->CreateCommittedResource
		(
			&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
			D3D12_HEAP_FLAG_NONE,
			&textureResourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&textures[texnumber].resource)
		);
	assert(SUCCEEDED(result));


	//�e�N�X�`���o�b�t�@�ւ̃f�[�^�]��
	//�S�~�b�v�}�b�v�ɂ���
	for(size_t i = 0; i < metadata.mipLevels; i++)
	{
		//�~�b�v�}�b�v���x�����w�肵�ăC���[�W���擾
		const Image* img = scratchImg.GetImage(i, 0, 0);
		//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
		result = textures[texnumber].resource->WriteToSubresource(
			(UINT)i,				
			nullptr,				//�S�̈�փR�s�[
			img->pixels,			//���f�[�^�A�h���X
			(UINT)img->rowPitch,	//�ꃉ�C���T�C�Y
			(UINT)img->slicePitch	//�ꖇ�T�C�Y
		);
		assert(SUCCEEDED(result));
	}

	///�V�F�[�_���\�[�X�r���[�̍쐬
	//�ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};	//�ݒ�\����
	srvDesc.Format = textureResourceDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;	//2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = textureResourceDesc.MipLevels;

	//�n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�̍쐬
	textures[texnumber].cpuDescHandleSRV = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		descHeap->GetCPUDescriptorHandleForHeapStart(), texnumber, 
		descriptorhandleIncrementSize);
	textures[texnumber].gpuDescHandleSRV = CD3DX12_GPU_DESCRIPTOR_HANDLE(
		descHeap->GetGPUDescriptorHandleForHeapStart(), texnumber, 
		descriptorhandleIncrementSize);

	dxCommon->GetDevice()->CreateShaderResourceView
	(
		textures[texnumber].resource.Get(),
		&srvDesc,
		textures[texnumber].cpuDescHandleSRV
	);
}

ID3D12Resource *TextureManager::GetSpriteTexBuffer(UINT texnumber)
{
	//�z��I�[�o�[�t���[�h�~
	assert(texnumber < maxTextureCount);

	return textures[texnumber].resource.Get();
}

void TextureManager::SetDescriptorHeaps(ID3D12GraphicsCommandList *commandList)
{
	//�e�X�N�`���p�f�X�N���v�^�q�[�v�̐ݒ�
	ID3D12DescriptorHeap* ppHeaps[] = {descHeap.Get()};
	commandList->SetDescriptorHeaps(_countof(ppHeaps),ppHeaps);
}

void TextureManager::SetShaderResourceView(ID3D12GraphicsCommandList *commandList, UINT RootParameterIndex, UINT texnumber)
{
	//�V�F�[�_�[���\�[�X�r���[(SRV)���Z�b�g
	commandList->SetGraphicsRootDescriptorTable(RootParameterIndex, textures[texnumber].gpuDescHandleSRV);
}