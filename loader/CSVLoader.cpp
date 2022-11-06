#include "CSVLoader.h"
#include <fstream>
#include <cassert>

using namespace std;

void CSVLoader::LoadPopData(std::string filaPath)
{
	//file�J��
	ifstream file;
	file.open(filaPath);
	assert(file.is_open());

	//file�|�{�𕶎���X�g���[���ɃR�s�[
	popCommands << file.rdbuf();
	file.close();
}

void CSVLoader::PopCommands(std::list<std::unique_ptr<BaseObjects>> obj, std::string objFilePath)
{
	//��s���̕����������ϐ�
	string line;

	//�R�}���h���[�v
	while(getline(popCommands, line)){
		//��s���̂���������X�g���[���ɕϊ����ĉ�͂��₷��
		istringstream line_stream(line);

		string word;
		//��؂�ōs�̑K��������擾
		getline(line_stream, word, ',');

		//"//"����n�܂�̂�comment
		if(word.find("//") == 0){
			//��΂�
			continue;
		}

		//POP�R�}���h
		if(word.find("POP") == 0){
			//X���W
			getline(line_stream, word, ',');
			float x = (float)atof(word.c_str());

			//Y���W
			getline(line_stream, word, ',');
			float y = (float)atof(word.c_str());

			//Z���W
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
