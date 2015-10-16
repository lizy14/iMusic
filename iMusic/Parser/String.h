/*
文件名: String.h
描　述: 字符串类

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once

#include <vector>

namespace N{
	class String : public std::vector<char>{
		static const int NOT_FOUND = 0;
	public:
		String();
		~String();
		int indexOf(char);
		int indexOf(String);
		String subString(int start=0, int end=-1, int length=-1);
		String operator +(String);
	};
}
