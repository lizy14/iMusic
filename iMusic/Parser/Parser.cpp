/*
�ļ���: Parser.cpp
�衡��: HTML ���������ʵ��

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "Parser.h"

N::Parser::Parser(String str){
	int prefix = str.indexOf(String("<div class=\"song_info_area\">"));
	int suffix = str.indexOf(String("<div class=\"music_list_area\">"));
	str = str.subString(prefix, suffix);
	songInfo.lyric=str;
	return;
}

N::Parser::~Parser(){
	return;
}