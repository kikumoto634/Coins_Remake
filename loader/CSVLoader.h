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
	/// 読み込み
	/// </summary>
	void LoadPopData(std::string filaPath);

	/// <summary>
	/// ポップコマンド
	/// </summary>
	void PopCommands(std::list<std::unique_ptr<BaseObjects>> obj, std::string objFilePath);

	/// <summary>
	/// ポップコマンド
	/// </summary>
	void Pop(std::list<std::unique_ptr<BaseObjects>> obj, std::string objFilePath, Vector3 pos);

private:
	//コマンド、書き込みコピー用
	std::stringstream popCommands;
};

