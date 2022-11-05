#pragma once
#include "Vector3.h"
#include "CollisionConfig.h"
#include <string>

class Collider
{
public:
	//�Փˎ�
	virtual void OnCollision(Collider* TouchCollision) = 0;

	//Get
	virtual const float GetWidth() = 0;
	virtual const float GetHeight() = 0;
	virtual const float GetDepth() = 0;
	virtual const std::string GetName() = 0;
	virtual const Vector3 GetPosition() = 0;

	const uint32_t GetCollisionAttribute()	{return collisionAttribute;}
	const uint32_t GetCollisionMask()	{return collisionMask;}

	void SetCollisionAttribute(const uint32_t bute)	{this->collisionAttribute = bute;}
	void SetCollisionMask(const uint32_t bute)	{this->collisionMask = bute;}

private:
	//�Փ˔��a
	float Width = 5.f;//�f�t�H���g�l
	float Height = 5.f;
	float Depth = 5.f;
	std::string name = "unknown";

	//�Փˑ���(���w)
	uint32_t collisionAttribute = 0xffffffff;
	//�Փ˃}�X�N(�G)
	uint32_t collisionMask = 0xffffffff;
};

