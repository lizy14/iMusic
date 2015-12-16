/*
文件名: Tests.h
描　述: 测试

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-17

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once

#include "List.h"
#include "Parser.h"
#include "SongInfo.h"
#include "Stack.h"
#include "CharString.h"
#include "CharStringList.h"

#include <iostream>
using std::cout;
using std::endl;

namespace Zhaoyang{
	namespace Test{
		void printBool(bool);
		void test();
		void parser();
		void str();
		void kmp();
		void stack();
		void seg();
	}
}
