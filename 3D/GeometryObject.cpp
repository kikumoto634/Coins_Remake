#include "GeometryObject.h"
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

GeometryObject::CommonGeometry* GeometryObject::common = nullptr;

void GeometryObject::StaticInitialize(DirectXCommon *dxCommon)
{
	common = new CommonGeometry();
	common->dxCommon = dxCommon;

	common->InitializeGraphicsPipeline();
	common->InitializeDescriptorHeap();

	common->geometryObjectManager = GeometryObjectManager::GetInstance();
	common->textureManager = TextureManager::GetInstance();
}

void GeometryObject::StaticFinalize()
{
	if(common != nullptr){
		delete common;
		common = nullptr;
	}
}

GeometryObject *GeometryObject::Create(UINT texNumber, XMFLOAT4 color)
{
	GeometryObject* object = new GeometryObject(texNumber, color);
	if(object == nullptr){
		return nullptr;
	}

	//������
	if(!object->Initialize(texNumber)){
		delete object;
		assert(0);
		return nullptr;
	}

	return object;
}

GeometryObject::GeometryObject()
{
}

GeometryObject::GeometryObject(UINT texNumber, XMFLOAT4 color)
{
	this->texNumber = texNumber;
	this->color = color;
}

bool GeometryObject::Initialize(UINT texNumber)
{
	HRESULT result;
	this->texNumber = texNumber;

	//�萔�o�b�t�@����
	{
		// �q�[�v�v���p�e�B
		CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		// ���\�[�X�ݒ�
		CD3DX12_RESOURCE_DESC resourceDesc =
		  CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff);

		//����
		result = common->dxCommon->GetDevice()->CreateCommittedResource(
			&heapProps,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&constBuffer)
		);
		assert(SUCCEEDED(result));

		//�萔�o�b�t�@�̓]��
		result = constBuffer->Map(0, nullptr, (void**)&constMap);
		assert(SUCCEEDED(result));
		constBuffer->Unmap(0, nullptr);
	}
	return true;
}

void GeometryObject::Update(WorldTransform worldTransform, Camera* camera)
{
	//�J�����̍s��擾
	const XMMATRIX& matWorld = worldTransform.matWorld;
	const XMMATRIX& matView = camera->GetMatView();
	const XMMATRIX& matProjection = camera->GetMatProjection();

	constMap->color = color;
	constMap->mat = matWorld * matView * matProjection;
}

void GeometryObject::Draw()
{
#pragma region ���ʕ`��R�}���h
	//�p�C�v���C���X�e�[�g�̐ݒ�
	common->dxCommon->GetCommandList()->SetPipelineState(common->pipelineState.Get());
	//���[�g�V�O�l�`���̐ݒ�
	common->dxCommon->GetCommandList()->SetGraphicsRootSignature(common->rootSignature.Get());
	//�v���~�e�B�u�`���ݒ�
	common->dxCommon->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
#pragma endregion

#pragma region �ʕ`��R�}���h
	//�f�X�N���v�^�q�[�v�̃Z�b�g
	ID3D12DescriptorHeap* ppHeaps[] = {common->basicDescHeap.Get()};
	common->dxCommon->GetCommandList()->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	//�萔�o�b�t�@�r���[(CBV�̐ݒ�R�}���h)
	common->dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffer->GetGPUVirtualAddress());
	//�f�X�N���v�^�q�[�v�̔z��
	common->textureManager->SetDescriptorHeaps(common->dxCommon->GetCommandList());
	//���_�o�b�t�@�̐ݒ�
	common->dxCommon->GetCommandList()->IASetVertexBuffers(0, 1, &common->geometryObjectManager->GetvbView());
	//�C���f�b�N�X�o�b�t�@�̐ݒ�
	common->dxCommon->GetCommandList()->IASetIndexBuffer(&common->geometryObjectManager->GetibView());

	//�V�F�[�_���\�[�X�r���[���Z�b�g
	common->textureManager->SetShaderResourceView(common->dxCommon->GetCommandList(), 1, texNumber);

	//�`��R�}���h
	common->dxCommon->GetCommandList()->DrawIndexedInstanced(common->geometryObjectManager->GetIndices(),1, 0, 0, 0);
#pragma endregion
}

void GeometryObject::CommonGeometry::InitializeGraphicsPipeline()
{
	HRESULT result;

	//�V�F�[�_�[�I�u�W�F�N�g
	ComPtr<ID3DBlob> vsBlob;
	ComPtr<ID3DBlob> psBlob;
	ComPtr<ID3DBlob> errorBlob;

	//���_�V�F�[�_�[�̓ǂݍ��݃R���p�C��
	result = D3DCompileFromFile(
		L"Resources/shader/GeometryVS.hlsl",		//�V�F�[�_�[�t�@�C����
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

	//�s�N�Z���V�F�[�_�[�̓ǂݍ��݃R���p�C��
	result = D3DCompileFromFile(
		L"Resources/shader/GeometryPS.hlsl",		//�V�F�[�_�[�t�@�C����
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
		{//�@���x�N�g��
			"NORMAL",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
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
	result = dxCommon->GetDevice()->CreateRootSignature(0,rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),IID_PPV_ARGS(&common->rootSignature));
	assert(SUCCEEDED(result));
	//�p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	pipelineDesc.pRootSignature = common->rootSignature.Get();

	//�p�C�v���C���X�e�[�g (�O���t�B�b�N�X�p�C�v���C���̐ݒ���܂Ƃ߂��̂��p�C�v���C���X�e�[�g�I�u�W�F�N�g(PSO))
	//�p�C�v���C���X�e�[�g�̐���
	result = dxCommon->GetDevice()->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&common->pipelineState));
	assert(SUCCEEDED(result));
}

void GeometryObject::CommonGeometry::InitializeDescriptorHeap()
{
	HRESULT result;

	D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = {};
	descriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	descriptorHeapDesc.NumDescriptors = common->geometryObjectManager->GetMaxObjectCount();
	result = dxCommon->GetDevice()->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&basicDescHeap));
	assert(SUCCEEDED(result));
}