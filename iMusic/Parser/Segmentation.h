/*
�ļ���: Segmentation
�衡��: ���ķִ����������

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once

#include "CharStringList.h"

#include <map>
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;
namespace Zhaoyang{
	class Segmentation{
	private:
		const static int MAX_WORD_LENGTH;
	public:
		static std::map<CharString, bool> vocabulary;
		static bool isWord(CharString);
		Segmentation(CharString);//��ȡ�����ļ������شʿ�
		~Segmentation(void);
		static CharStringList exec(CharString);//�Դ�����ַ���ִ�зִʣ����طִʽ��
	};
}
