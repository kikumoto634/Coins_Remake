#include "CSVLoader.h"
#include <fstream>
#include <cassert>

using namespace std;

void CSVLoader::LoadPopData(string filaPath)
{
	//file開く
	ifstream file;
	file.open(filaPath);
	assert(file.is_open());

	//file培養を文字列ストリームにコピー
	popCommands << file.rdbuf();
	file.close();
}

void CSVLoader::PopCommands(list<unique_ptr<BaseObjects>> obj, string objFilePath)
{
	//待機処理
	if(IsWait){
		waitTime--;
		if(waitTime <= 0){
			//待機完了
			IsWait = false;
		}
		return;
	}

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
			obj.push_back(move(Pop(objFilePath, Vector3(x, y, z))));
		}
		else if(word.find("WAIT") == 0){
			getline(line_stream,word, ',');

			//待ち時間
			int32_t waitTime = atoi(word.c_str());

			//待機開始
			IsWait = true;
			this->waitTime = waitTime;

			break;
		}
	}
}

unique_ptr<BaseObjects> CSVLoader::Pop(string objFilePath, Vector3 pos)
{
	unique_ptr<BaseObjects> newObj = make_unique<BaseObjects>();
	newObj->Initialize(objFilePath);
	newObj->SetVector3(pos);

	return newObj;
}
