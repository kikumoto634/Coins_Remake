#include "Sprite.h"
#include "Vector2.h"

class BaseSprite
{
public:
	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize(UINT textureNumber);

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update();

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// �㏈��
	/// </summary>
	virtual void Finalize();

	//Setter
	void SetVector2(Vector2 position)	{this->position = position;}
	void SetSize(Vector2 size)	{this->size = size;}

protected:
	Sprite* sprite;
	Vector2 position = {0,0};
	Vector2 size = {100,100};

	bool IsDead = false;
};