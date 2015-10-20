/*
文件名: Parser.cpp
描　述: HTML 解析器类的实现

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "Parser.h"

Zhaoyang::Parser::Parser(CharString str){
	int prefix = str.indexOf(CharString("<div class=\"song_info_area\">"));
	int suffix = str.indexOf(CharString("<div class=\"music_list_area\">"));
	str = str.subString(prefix, suffix);
	songInfo.lyric=str;
	return;
}

Zhaoyang::Parser::~Parser(){
	return;
}