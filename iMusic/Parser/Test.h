/*
�ļ���: Tests.h
�衡��: ����

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-17

������: Visual Studio 2012 (MSVC++ 11.0)
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
