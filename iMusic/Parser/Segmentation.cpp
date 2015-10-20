/*
文件名: Segmentation.cpp
描　述: 中文分词器类的实现

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "Segmentation.h"
namespace Zhaoyang{

	Segmentation::Segmentation(void){
	}

	Segmentation::~Segmentation(void){
	}

	CharStringList& Segmentation::exec(CharString){
		CharStringList *list = new CharStringList();
		list->push(CharString("THIS_IS_WORD_A"));
		list->push(CharString("THIS_IS_WORD_B"));
		list->push(CharString("THIS_IS_WORD_C"));
		return *list;
	}
}