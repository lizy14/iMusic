/*
�ļ���: Segmentation.cpp
�衡��: ���ķִ������ʵ��

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "Segmentation.h"
namespace Zhaoyang{
	const int Segmentation::MAX_WORD_LENGTH = 8;
	std::map<CharString, bool> Segmentation::vocabulary;
	bool Segmentation::isWord(CharString word){
		return vocabulary.find(word) != vocabulary.end();
	}
	
	//constructor: load library here
	Segmentation::Segmentation(CharString configFileName){
		
		std::ifstream file(configFileName);
		std::string vocabularyFileName;
		getline(file, vocabularyFileName);
		file.close();
		file.open(vocabularyFileName);
		std::string _;
		int i=0;
		while(!file.eof()){
			getline(file, _);
			vocabulary[_] = true;
		}
	}

	Segmentation::~Segmentation(void){
	}

	CharStringList Segmentation::exec(CharString str){
		CharStringList list = CharStringList();
		if(str.length() == 0)
			return list;
		int iA, iB; //starting/ending index 
		return list;
	}
}
