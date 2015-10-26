/*
文件名: Segmentation
描　述: 中文分词器类的声明

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
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
		Segmentation(CharString);//读取配置文件，加载词库
		~Segmentation(void);
		CharStringList exec(CharString);//对传入的字符串执行分词，返回分词结果
	};
}
