#include "CSVLoader.h"
#include <fstream>
#include <cassert>

using namespace std;

void CSVLoader::LoadPopData(std::string filaPath)
{
	//file開く
	ifstream file;
	file.open(filaPath);
	assert(file.is_open());

	//file培養を文字列ストリームにコピー
	popCommands << file.rdbuf();
	file.close();
}

void CSVLoader::PopCommands(std::list<std::unique_ptr<BaseObjects>> obj, std::string objFilePath)
{
	//一行分の文字列を入れる変数
	string line;

	//コマンドループ
	while(getline(popCommands, line)){
		//一行分のっ文字列をストリームに変換して解析しやすく
		istringstream line_stream(line);

		string word;
		//区切りで行の銭湯文字列取得
		getline(line_stream, word, ',');

		//"//"から始まるのはcomment
		if(word.find("//") == 0){
			//飛ばす
			continue;
		}

		//POPコマンド
		if(word.find("POP") == 0){
			//X座標
			getline(line_stream, word, ',');
			float x = (float)atof(word.c_str());

			//Y座標
			getline(line_stream, word, ',');
			float y = (float)atof(word.c_str());

			//Z座標
			getline(line_stream, word, ',');
			float z = (float)atof(word.c_str());
			//POP
			Pop(obj, objFilePath, Vector3(x, y, z));
		}
	}
}

void CSVLoader::Pop(std::list<std::unique_ptr<BaseObjects>> obj, std::string objFilePath, Vector3 pos)
{
	unique_ptr<BaseObjects> newObj = make_unique<BaseObjects>();
	newObj->Initialize(objFilePath);
	newObj->SetVector3(pos);

	obj.push_back(move(newObj));
}
