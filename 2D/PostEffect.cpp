#include "PostEffect.h"

PostEffect* PostEffect::Create(UINT texNumber, Vector2 pos, XMFLOAT4 color, Vector2 anchorpoint, bool isFlipX, bool isFlipY)
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
	PostEffect* post =
		new PostEffect(texNumber, {pos.x,pos.y,0.f}, size, color, anchorpoint, isFlipX, isFlipY);
	if (post == nullptr) {
		return nullptr;
	}

	// ������
	if (!post->Initialize(texNumber)) {
		delete post;
		assert(0);
		return nullptr;
	}

	return post;
}


PostEffect::PostEffect(UINT texnumber, Vector3 pos, Vector2 size, XMFLOAT4 color, Vector2 anchorpoint, bool isFlipX, bool isFlipY)
	:Sprite(
		texnumber,
		pos,
		size,
		color,
		anchorpoint,
		isFlipX,
		IsFlipY)
{
}

void PostEffect::Draw()
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

	//�p�C�v���C���X�e�[�g�̐ݒ�
	common->dxCommon->GetCommandList()->SetPipelineState(common->pipelinestate.Get());
	//���[�g�V�O�l�`���̐ݒ�
	common->dxCommon->GetCommandList()->SetGraphicsRootSignature(common->rootsignature.Get());
	//�v���~�e�B�u�`���ݒ�
	common->dxCommon->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

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
