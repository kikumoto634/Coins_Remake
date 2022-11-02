#include "ViewProjection.h"

using namespace DirectX;

void ViewProjection::UpdateViewMatrix()
{
	//�r���[�ϊ��s��
	XMFLOAT3 leye = {eye.x,eye.y,eye.z};
	XMFLOAT3 ltarget = {target.x,target.y,target.z};
	XMFLOAT3 lup = {up.x,up.y,up.z};

	matView = XMMatrixLookAtLH(XMLoadFloat3(&leye), XMLoadFloat3(&ltarget), XMLoadFloat3(&lup));	
}

void ViewProjection::UpdateProjectionMatrix(int width, int height)
{
	//�������e
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45.0f),	//�㉺��p45��
		(float)width / height,			//aspect��(��ʉ���/��ʏc��)
		0.1f, 1000.0f				//�O�[�A���[
	);
}
