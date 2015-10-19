/*
文件名: String.h
描　述: 字符串类（以`std::vector<char>`为基类，自行实现串的模式匹配等算法）

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once

#include <vector>
#include <string>
#include <ostream>

namespace N{
	class String : public std::vector<char>{
		static const int NOT_FOUND = -1;
	public:
		int length(){
			return this->size();
		}
		String();
		~String();
		int indexOf(char);
		int indexOf(String);
		String subString(int start, int end=-1);
		
		
		//conversion from/to std::string
		operator std::string(){
			std::string str;
			int len = length();
			for(int i=0; i<len; i++){
				str.push_back(operator[](i));
			}
			return str;
		}
		String(std::string str){
			for(char chr: str)
				push_back(chr);
			return;
		}
		
	};
	std::ostream& operator<< (std::ostream& os, const String& str);
	String operator+(const String& str1, const String& str2);
}

