#include "ViewProjection.h"

using namespace DirectX;

void ViewProjection::UpdateViewMatrix()
{
	//r[Ï·sñ
	XMFLOAT3 leye = {eye.x,eye.y,eye.z};
	XMFLOAT3 ltarget = {target.x,target.y,target.z};
	XMFLOAT3 lup = {up.x,up.y,up.z};

	matView = XMMatrixLookAtLH(XMLoadFloat3(&leye), XMLoadFloat3(&ltarget), XMLoadFloat3(&lup));	
}

void ViewProjection::UpdateProjectionMatrix(int width, int height)
{
	//§e
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(angle),	//ãºæp
		(float)width / height,			//aspectä(æÊ¡/æÊc)
		0.1f, 1300.0f				//O[A[
	);
}
