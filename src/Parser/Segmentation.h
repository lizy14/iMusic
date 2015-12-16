/*
�ļ���: Segmentation
�衡��: ���ķִ����������

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once

#include "CharStringList.h"

#include <set>
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;
namespace Zhaoyang{
	typedef std::set<CharString> Vocabulary;
	class Segmentation{
	private:
		const static int MAX_WORD_LENGTH;
		const static int MIN_WORD_LENGTH;
	public:
		Vocabulary vocabulary;
		bool isWord(CharString);
		bool isPunctuation(CharString);
		Segmentation(CharString);//��ȡ�����ļ������شʿ�
		~Segmentation(void);
		CharStringList exec(CharString);//�Դ�����ַ���ִ�зִʣ����طִʽ��
	};
}
