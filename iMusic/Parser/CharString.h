/*
文件名: CharString.h
描　述: 字符串类（以`std::vector<char>`为基类，自行实现串的模式匹配等算法）

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once

#include <vector>
#include <string>
#include <ostream>

namespace Zhaoyang{
	class CharString{
		char* head;
		int len;
		int capacity;
		static const int REALLOCATE_SIZE;
		static const int NOT_FOUND = -1;
	public:
		char& operator[](int i) const;
		void append(char chr);
		int length() const;
		CharString();
		~CharString();
		int indexOf(char) const;
		int indexOf(CharString) const;
		CharString subString(int start, int end=-1);
		
		//conversion from/to std::string
		CharString(std::string str);
		operator std::string(){
			std::string str;
			int len = length();
			for(int i=0; i<len; i++){
				str.push_back(operator[](i));
			}
			return str;
		}
		
	};
	std::ostream& operator<< (std::ostream& os, const CharString& str);
	CharString operator+(const CharString& str1, const CharString& str2);
}

