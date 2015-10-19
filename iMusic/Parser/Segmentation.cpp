/*
文件名: Segmentation.cpp
描　述: 中文分词器类的实现

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "Segmentation.h"


N::Segmentation::Segmentation(void){
}

N::Segmentation::~Segmentation(void){
}

StringList& N::Segmentation::exec(String){
	StringList *list = new StringList();
	list->push(String("THIS_IS_WORD_A"));
	list->push(String("THIS_IS_WORD_B"));
	list->push(String("THIS_IS_WORD_C"));
	return *list;
}
