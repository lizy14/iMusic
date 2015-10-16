/*
�ļ���: String.h
�衡��: �ַ�����

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
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
