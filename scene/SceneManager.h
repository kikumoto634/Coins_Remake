#pragma once
#include "GameSceneBase.h"
#include <map>
#include <string>

class SceneManager
{
public:
	using string = std::string;

public:
	SceneManager();
	~SceneManager();

	void Update();
	void Draw();

	//�V�[���ǉ�
	void Add(const string& name, GameSceneBase* scene);
	//�`�F���W
	void Change(const string& name);
	//�N���A
	void Clear();

	//����
	string GetNowScene();
	string GetNextScene();
	bool GetIsAlive();

private:
	//�S���O�ƑS�V�[��������
	std::map<std::string, GameSceneBase*> scenes;

	//����
	GameSceneBase* nowScene;

	bool IsAllEnd;
};

