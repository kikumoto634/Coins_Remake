#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <list>

#include "Vector3.h"
#include "BaseObjects.h"

class CSVLoader
{
public:
	/// <summary>
	/// �ǂݍ���
	/// </summary>
	void LoadPopData(std::string filaPath);

	/// <summary>
	/// �|�b�v�R�}���h
	/// </summary>
	void PopCommands(std::list<std::unique_ptr<BaseObjects>> obj, std::string objFilePath);

	/// <summary>
	/// �|�b�v�R�}���h
	/// </summary>
	void Pop(std::list<std::unique_ptr<BaseObjects>> obj, std::string objFilePath, Vector3 pos);

private:
	//�R�}���h�A�������݃R�s�[�p
	std::stringstream popCommands;
};

