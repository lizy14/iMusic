/*
文件名: CharString.h
描　述: 字符串类

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once


#include <string>
#include <ostream>

namespace Zhaoyang{
	class CharString{
		char* head;
		int len;
		int capacity;
	public:
		static const int NOT_FOUND = -1;
	public:
		CharString();
		~CharString();
		CharString(const CharString& str);
		CharString(CharString& str);
		CharString& operator=(const CharString& str);

		char& operator[](int i) const;
		void append(char chr);
		int length() const;

		static bool isSpace(char);
		static bool isASCII(char);
		CharString trim();
		
		int indexOf(char, int=0) const;
		int indexOf(CharString, int=0) const;
		CharString subString(int start, int end=-1) const;
		
		//conversion from/to std::string
		CharString(const std::string str);
		operator std::string(){
			std::string str;
			int len = length();
			for(int i=0; i<len; i++){
				str.push_back(operator[](i));
			}
			return str;
		}

		bool operator<(const CharString& str1) const;
		bool operator>(const CharString& str1) const{
			return str1 < *this;
		}
	};
	std::ostream& operator<< (std::ostream& os, const CharString& str);
	
	CharString operator+(const CharString& str1, const CharString& str2);
	bool operator==(const CharString& str1, const CharString& str2);
}

