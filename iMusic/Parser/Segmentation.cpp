/*
�ļ���: Segmentation.cpp
�衡��: ���ķִ������ʵ��

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
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
