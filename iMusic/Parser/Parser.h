/*
�ļ���: Parser.h
�衡��: HTML ��������

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once
#include "String.h"
#include "SongInfo.h"
#include "List.h"

namespace N{
	class Parser{
	public:
		SongInfo songInfo;
	public:
		Parser(String);
		~Parser();
	};
}
