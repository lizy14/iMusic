/*
�ļ���: Parser.h
�衡��: HTML ��������

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
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
		Parser(CharString);//���ش������� html
		~Parser();
		SongInfo getSongInfo();//���ؽ������
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
