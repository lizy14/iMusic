/*
�ļ���: Segmentation.cpp
�衡��: ���ķִ������ʵ��

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "Segmentation.h"
namespace Zhaoyang{

	//constructor: load library here
	Segmentation::Segmentation(CharString configFileName){
		return;
		std::ifstream file(configFileName);
		std::string vocabularyFileName;
		getline(file, vocabularyFileName);
		file.close();
		file.open(vocabularyFileName);
		std::string _;
		while(!file.eof()){
			getline(file, _);
			//add into vocabulary
		}
	}

	Segmentation::~Segmentation(void){
	}

	CharStringList Segmentation::exec(CharString){
		CharStringList list = CharStringList();
		list.push(CharString("THIS_IS_WORD_A"));
		list.push(CharString("THIS_IS_WORD_B"));
		list.push(CharString("THIS_IS_WORD_C"));
		return list;
	}
}