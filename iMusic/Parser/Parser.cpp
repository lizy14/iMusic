/*
文件名: Parser.cpp
描　述: HTML 解析器类的实现

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "Parser.h"
#include <iostream>
using namespace std;
namespace Zhaoyang{
	class Tag{
	public:
		CharString tagName;
		Tag(CharString _):tagName(_){}
		Tag(){}
	};
	template<class T>T min(T a, T b){return (a<b?a:b);}
	Parser::Parser(CharString str){
		int prefix = str.indexOf(CharString("<div class=\"song_info_area\">"));
		int suffix = str.indexOf(CharString("<div class=\"music_list_area\">"));
		str = str.subString(prefix, suffix);
		songInfo.lyric=str; return;
		str=CharString("<div class=\"song_info_area\"><a><b><c class></c></b></a><d></d></div>");
		cout << str;


		Stack<Tag> stack;
		try{
			for(int i=0; i<str.length(); ){
				while(i<str.length() && str[i]!='<'){
					i++;
				}
				//found '<'

				if(i<str.length() && str[i+1]=='/'){
					//found `</`
					//i = str.indexOf('>')+1;
					i++;
				}else{
					//found a new tag name
					int endOfTagName = min(str.indexOf(' ', i),str.indexOf('>', i)) - 1;
					CharString tagName = str.subString(i+1, endOfTagName+1);
					cout << endl << tagName;
					stack.push(tagName);
					i = str.indexOf('>', i) + 1;
				}
			}
		}catch(...){

		}
		return;
	}

	Parser::~Parser(){
		return;
	}
}