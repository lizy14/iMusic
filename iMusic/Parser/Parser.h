/*
文件名: Parser.h
描　述: HTML 解析器类

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once
#include "CharString.h"
#include "SongInfo.h"
#include "Stack.h"

namespace Zhaoyang{
	class Parser{
	public:
		SongInfo songInfo;
	public:
		Parser(CharString);
		~Parser();
	};
}
