/*
文件名: Segmentation
描　述: 中文分词器类的声明

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once

#include "StringList.h"
using N::String;
using N::StringList;

namespace N{
	class Segmentation{
	public:
		Segmentation(void);
		~Segmentation(void);
		static StringList& exec(String);
	};
}
