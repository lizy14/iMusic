/*
文件名: Parser.h
描　述: HTML 解析器类

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once
#include "CharString.h"
#include "SongInfo.h"
#include "Stack.h"

namespace Zhaoyang{
	class Tag;

	class Parser{
	private:
		SongInfo songInfo;
		List<Tag> allTags;
	public:
		CharString str;
	public:
		Parser(CharString);//加载待解析的 html
		~Parser();
		SongInfo getSongInfo();//返回解析结果
	};

	int max_(int, int);
	int min_(int, int);
	CharString innerText(CharString);
	

	class Tag{
	public:
		CharString tagName;
		int start;
		int inner;
		int end;
		/*   01234567890123456789012345
		     <p class>hello, world</p><
		     ^        ^               ^ */
		Tag(CharString _):tagName(_){}
		Tag(){}
	};
}
