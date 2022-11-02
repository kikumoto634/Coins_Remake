#include "Sprite.h"

#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

Sprite::Common* Sprite::common = nullptr;

void Sprite::StaticInitialize(DirectXCommon* dxCommon,
	int window_width, int window_height, const std::string& directoryPath)
{
	common = new Common();

	common->dxCommon = dxCommon;

	//�O���t�B�b�N�X�p�C�v���C������
	common->InitializeGraphicsPipeline(directoryPath);

	//���s���e�̎ˉe�s�񐶐�
	common->matProjection = XMMatrixOrthographicOffCenterLH
	(
		0.f, (float)window_width,
		(float)window_height, 0.f,
		0.f, 1.f
	);
}

void Sprite::StaticFinalize()
{
	//���
	if(common != nullptr)
	{
		delete common;
		common = nullptr;
	}
}

void Sprite::SetPipelineState()
{
	//�p�C�v���C���X�e�[�g�̐ݒ�
	common->dxCommon->GetCommandList()->SetPipelineState(common->pipelinestate.Get());
	//���[�g�V�O�l�`���̐ݒ�
	common->dxCommon->GetCommandList()->SetGraphicsRootSignature(common->rootsignature.Get());
	//�v���~�e�B�u�`���ݒ�
	common->dxCommon->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

Sprite *Sprite::Create(UINT texNumber, Vector2 pos, XMFLOAT4 color, Vector2 anchorpoint, bool isFlipX, bool isFlipY)
{
	// ���T�C�Y
	Vector2 size = {100.0f, 100.0f};

	{
		// �e�N�X�`�����擾
		//const D3D12_RESOURCE_DESC& resDesc = common->textureManager->GetSpriteTexBuffer(texNumber)->GetDesc();
		const D3D12_RESOURCE_DESC& resDesc = TextureManager::GetInstance()->GetSpriteTexBuffer(texNumber)->GetDesc();
		// �X�v���C�g�̃T�C�Y���e�N�X�`���̃T�C�Y�ɐݒ�
		size = {(float)resDesc.Width, (float)resDesc.Height};
	}

	// Sprite�̃C���X�^���X�𐶐�
	Sprite* sprite =
		new Sprite(texNumber, {pos.x,pos.y,0.f}, size, color, anchorpoint, isFlipX, isFlipY);
	if (sprite == nullptr) {
		return nullptr;
	}

	// ������
	if (!sprite->Initialize(texNumber)) {
		delete sprite;
		assert(0);
		return nullptr;
	}

	return sprite;
}

Sprite::Sprite()
{
}

Sprite::Sprite(UINT texnumber, Vector3 pos, Vector2 size, XMFLOAT4 color, Vector2 anchorpoint, bool isFlipX, bool isFlipY)
{
	this->texNumber = texnumber;
	this->position = pos;
	this->size = size;
	this->color = color;
	this->matWorld = XMMatrixIdentity();
	this->anchorpoint = anchorpoint;
	this->IsFlipX = isFlipX;
	this->IsFlipY = isFlipY;
	this->texSize = size;
}

bool Sprite::Initialize(UINT texNumber)
{
	HRESULT result;

	//�e�N�X�`���ԍ��R�s�[
	this->texNumber = texNumber;

	//�w��ԍ��̉摜���Ǎ������Ȃ�
	if(TextureManager::GetInstance()->GetSpriteTexBuffer(texNumber))
	{
		//�e�N�X�`�����擾
		resourceDesc = TextureManager::GetInstance()->GetSpriteTexBuffer(texNumber)->GetDesc();

		//�X�v���C�g�̑傫�����摜�̉𑜓x�ɍ��킹��
		this->size = {(float)resourceDesc.Width, (float)resourceDesc.Height};
	}

	{
		// �q�[�v�v���p�e�B
		CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		// ���\�[�X�ݒ�
		CD3DX12_RESOURCE_DESC resourceDesc =
		  CD3DX12_RESOURCE_DESC::Buffer(sizeof(VertexPosUv) * common->vertNum);

		//���_�o�b�t�@����
		result = common->dxCommon->GetDevice()->CreateCommittedResource(
			&heapProps,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&this->vertBuff)
		);
		assert(SUCCEEDED(result));
	}

	//���_�o�b�t�@�ւ̃f�[�^�]��
	SpriteTransferVertexBuffer();

	//���_�o�b�t�@�r���[�̍쐬
	this->vbView.BufferLocation = this->vertBuff->GetGPUVirtualAddress();
	this->vbView.SizeInBytes = sizeof(VertexPosUv) * common->vertNum;
	this->vbView.StrideInBytes = sizeof(VertexPosUv);

	{
		// �q�[�v�v���p�e�B
		CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		// ���\�[�X�ݒ�
		CD3DX12_RESOURCE_DESC resourceDesc =
		  CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff);

		//�萔�o�b�t�@�̐���
		result = common->dxCommon->GetDevice()->CreateCommittedResource(
			&heapProps,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&this->constBuffData)
		);
		assert(SUCCEEDED(result));
	}

	//�萔�o�b�t�@�̃f�[�^�]��
	result = this->constBuffData->Map(0, nullptr, (void**)&constMap);
	if(SUCCEEDED(result)){
		constMap->color = XMFLOAT4(1.f, 1.f, 1.f, 1.f);
		constMap->mat = common->matProjection;
		this->constBuffData->Unmap(0, nullptr);
	}

	return true;
}

//�X�v���C�g�P�̒��_�o�b�t�@�̓]��
void Sprite::SpriteTransferVertexBuffer()
{
	HRESULT result = S_FALSE;

	enum {LB, LT, RB, RT};

	float left = (0.f - this->anchorpoint.x)* this->size.x;
	float right = (1.f - this->anchorpoint.x)* this->size.x;
	float top = (0.f - this->anchorpoint.y)* this->size.y;
	float bottom = (1.f - this->anchorpoint.y)* this->size.y;

	if(this->IsFlipX)
	{//���E����ւ�
		left = -left;
		right = -right;
	}
	if(this->IsFlipY)
	{//�㉺���]
		top = -top;
		bottom = -bottom;
	}

	//���_�f�[�^
	VertexPosUv vertices[4];

	vertices[LB].pos = {left, bottom, 0.f};
	vertices[LT].pos = {left, top, 0.f};
	vertices[RB].pos = {right, bottom, 0.f};
	vertices[RT].pos = {right, top, 0.f};

	//UV�v�Z
	//�w��ԍ��̉摜���Ǎ��ς݂Ȃ�
	if(TextureManager::GetInstance()->GetSpriteTexBuffer(texNumber))
	{
		float tex_left = this->texLeftTop.x / resourceDesc.Width;
		float tex_right = (this->texLeftTop.x + this->texSize.x) / resourceDesc.Width;
		float tex_top = this->texLeftTop.y / resourceDesc.Height;
		float tex_bottom = (this->texLeftTop.y + this->texSize.y) / resourceDesc.Height;
	
		vertices[LB].uv = {tex_left, tex_bottom};
		vertices[LT].uv = {tex_left, tex_top};
		vertices[RB].uv = {tex_right, tex_bottom};
		vertices[RT].uv = {tex_right, tex_top};
	}

	//���_�o�b�t�@�̃f�[�^�]��
	result = this->vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	memcpy(vertMap, vertices,sizeof(vertices));
	this->vertBuff->Unmap(0,nullptr);
}

void Sprite::Draw()
{
	//���[���h�s��̍X�V
	this->matWorld = XMMatrixIdentity();
	//Z����]
	this->matWorld *= XMMatrixRotationZ(XMConvertToRadians(this->rotation));
	//���s�ړ�
	this->matWorld *= XMMatrixTranslation(this->position.x, this->position.y, this->position.z);

	//�萔�o�b�t�@�̓]��
	HRESULT result;
	result = this->constBuffData->Map(0,nullptr, (void**)&constMap);
	assert(SUCCEEDED(result));
	constMap->mat = this->matWorld * common->matProjection;
	constMap->color = this->color;
	this->constBuffData->Unmap(0, nullptr);

	if(this->IsInvisible){
		return ;
	}

	//���_�o�b�t�@�̃Z�b�g
	common->dxCommon->GetCommandList()->IASetVertexBuffers(0,1,&this->vbView);
	//�萔�o�b�t�@���Z�b�g
	common->dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(0, this->constBuffData->GetGPUVirtualAddress());
	//�e�X�N�`���p�f�X�N���v�^�q�[�v�̐ݒ�
	TextureManager::GetInstance()->SetDescriptorHeaps(common->dxCommon->GetCommandList());
	//�V�F�[�_�[���\�[�X�r���[���Z�b�g
	TextureManager::GetInstance()->SetShaderResourceView(common->dxCommon->GetCommandList(), 1, this->texNumber);
	//�|���S���̕`��
	common->dxCommon->GetCommandList()->DrawInstanced(4, 1, 0, 0);
}

void Sprite::SetPosition(Vector2 pos)
{
	this->position.x = pos.x;
	this->position.y = pos.y;

	//���_���̓]��
	SpriteTransferVertexBuffer();
}

void Sprite::SetSize(Vector2 size)
{
	this->size.x = size.x;
	this->size.y = size.y;
	
	//���_���̓]��
	SpriteTransferVertexBuffer();
}

void Sprite::SetAnchorpoint(Vector2 pos)
{
	this->anchorpoint.x = pos.x;
	this->anchorpoint.y = pos.y;

	SpriteTransferVertexBuffer();
}

void Sprite::SetTextureRect(float tex_x, float tex_y, float tex_width, float tex_height)
{
	this->texLeftTop = {tex_x, tex_y};
	this->texSize = {tex_width, tex_height};

	SpriteTransferVertexBuffer();
}

void Sprite::SetIsFlipX(bool IsFlipX)
{
	this->IsFlipX = IsFlipX;

	SpriteTransferVertexBuffer();
}

void Sprite::SetIsFlipY(bool IsFlipY)
{
	this->IsFlipY = IsFlipY;

	SpriteTransferVertexBuffer();
}

void Sprite::SetColor(XMFLOAT4 color)
{
	this->color = color;
	SpriteTransferVertexBuffer();
}

void Sprite::Common::InitializeGraphicsPipeline(const std::string& directoryPath)
{
	HRESULT result;

	///���_�V�F�[�_�[file�̓ǂݍ��݂ƃR���p�C��
	ComPtr<ID3DBlob> vsBlob ;			//���_�V�F�[�_�[�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob ;			//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g
	ComPtr<ID3DBlob> errorBlob ;		//�G���[�I�u�W�F�N�g

	std::string fullPathVS = directoryPath + "/SpriteVS.hlsl";
	wchar_t wFullPathVS[256];
	MultiByteToWideChar(CP_ACP, 0, fullPathVS.c_str(), -1, wFullPathVS, _countof(wFullPathVS));

	//���_�V�F�[�_�[�̓ǂݍ��݃R���p�C��
	result = D3DCompileFromFile(
		wFullPathVS,		//�V�F�[�_�[�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	//�C���N���[�h�\�ɂ���
		"main", "vs_5_0",					//�G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,	//�f�o�b�N�p�ݒ�
		0,
		&vsBlob, &errorBlob);
	//�G���[�Ȃ�
	if(FAILED(result)){
		//errorBlob����G���[���e��string�^�ɃR�s�[
		std::string error;
		error.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
					errorBlob->GetBufferSize(),
					error.begin());
		error += "\n";
		//�G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(error.c_str());
		assert(0);
	}

	std::string fullPathPS = directoryPath + "/SpritePS.hlsl";
	wchar_t wFullPathPS[256];
	MultiByteToWideChar(CP_ACP, 0, fullPathPS.c_str(), -1, wFullPathPS, _countof(wFullPathPS));

	//�s�N�Z���V�F�[�_�[�̓ǂݍ��݃R���p�C��
	result = D3DCompileFromFile(
		wFullPathPS,		//�V�F�[�_�[�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	//�C���N���[�h�\�ɂ���
		"main", "ps_5_0",					//�G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,	//�f�o�b�N�p�ݒ�
		0,
		&psBlob, &errorBlob);
	//�G���[�Ȃ�
	if(FAILED(result)){
		//errorBlob����G���[���e��string�^�ɃR�s�[
		std::string error;
		error.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
					errorBlob->GetBufferSize(),
					error.begin());
		error += "\n";
		//�G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(error.c_str());
		assert(0);
	}


	///���_���C�A�E�g
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
	
		{//xyz���W
			"POSITION",										//�Z�}���e�B�b�N��
			0,												//�����Z�}���e�B�b�N������������Ƃ��Ɏg���C���f�b�N�X
			DXGI_FORMAT_R32G32B32_FLOAT,					//�v�f���ƃr�b�g����\�� (XYZ��3��float�^�Ȃ̂�R32G32B32_FLOAT)
			0,												//���̓X���b�g�C���f�b�N�X
			D3D12_APPEND_ALIGNED_ELEMENT,					//�f�[�^�̃I�t�Z�b�g�l (D3D12_APPEND_ALIGNED_ELEMENT���Ǝ����ݒ�)
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		//���̓f�[�^��� (�W����D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA)
			0												//��x�ɕ`�悷��C���X�^���X��
		},
		{//uv���W
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
	};

	///���[�g�p�����[�^
	//�f�X�N���v�^�����W�̐ݒ�
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV{};
	descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);


	//�ݒ�
	////�萔�o�b�t�@ 0��
	CD3DX12_ROOT_PARAMETER rootParam[2] = {};
	////�萔�@0�� material
	rootParam[0].InitAsConstantBufferView(0);
	////�e�N�X�`�����W�X�^ 0��
	rootParam[1].InitAsDescriptorTable(1, &descRangeSRV);


	///<summmary>
	///�O���t�B�b�N�X�p�C�v���C��
	///<summary/>
	
	//�O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
	//�V�F�[�_�[�ݒ�
	pipelineDesc.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	pipelineDesc.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());
	
	//�T���v���}�X�N�ݒ�
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;	//�W���ݒ�
	//���X�^���C�U�ݒ� �w�ʃJ�����O	�|���S�����h��Ԃ�	�[�x�N���b�s���O�L��
	pipelineDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
	//�u�����h�X�e�[�g
	//�����_�[�^�[�Q�b�g�̃u�����h�ݒ�
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = pipelineDesc.BlendState.RenderTarget[0];
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;	//RGBA���ׂẴ`�����l����`��
	//���ʐݒ�
	blenddesc.BlendEnable = true;						//�u�����h��L���ɂ���
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;		//���Z
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;			//�\�[�X�̒l��100% �g��	(�\�[�X�J���[			 �F ������`�悵�悤�Ƃ��Ă���F)
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;		//�f�X�g�̒l��  0% �g��	(�f�X�e�B�l�[�V�����J���[�F ���ɃL�����o�X�ɕ`����Ă���F)
	//�e��ݒ�
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;	//�ݒ�
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;			//�\�[�X�̒l�� ��% �g��
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;	//�f�X�g�̒l�� ��% �g��
	//���_���C�A�E�g�ݒ�
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
	pipelineDesc.InputLayout.NumElements = _countof(inputLayout);
	//�}�`�̌`��ݒ� (�v���~�e�B�u�g�|���W�[)
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	//���̑��ݒ�
	pipelineDesc.NumRenderTargets = 1;		//�`��Ώۂ͈��
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;	//0~255�w���RGBA
	pipelineDesc.SampleDesc.Count = 1;	//1�s�N�Z���ɂ�1��T���v�����O
	//�f�v�X�X�e���V���X�e�[�g�̐ݒ�	(�[�x�e�X�g���s���A�������݋��A�[�x������������΋���)
	pipelineDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	pipelineDesc.DepthStencilState.DepthEnable = false;
	pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;	//�[�x�l�t�H�[�}�b�g

	///�e�N�X�`���T���v���[
	//�ݒ�
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);


	//���[�g�V�O�l�`�� (�e�N�X�`���A�萔�o�b�t�@�ȂǃV�F�[�_�[�ɓn�����\�[�X�����܂Ƃ߂��I�u�W�F�N�g)
	//�ݒ�
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.Init_1_0(_countof(rootParam), rootParam,1, &samplerDesc,D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
	//�V���A���C�Y
	ComPtr<ID3DBlob> rootSigBlob;
	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob,&errorBlob);
	assert(SUCCEEDED(result));
	result = dxCommon->GetDevice()->CreateRootSignature(0,rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),IID_PPV_ARGS(&common->rootsignature));
	assert(SUCCEEDED(result));
	//�p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	pipelineDesc.pRootSignature = common->rootsignature.Get();

	//�p�C�v���C���X�e�[�g (�O���t�B�b�N�X�p�C�v���C���̐ݒ���܂Ƃ߂��̂��p�C�v���C���X�e�[�g�I�u�W�F�N�g(PSO))
	//�p�C�v���C���X�e�[�g�̐���
	result = dxCommon->GetDevice()->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&common->pipelinestate));
	assert(SUCCEEDED(result));
}
