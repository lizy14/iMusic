/*
文件名: Parser.cpp
描　述: HTML 解析器类的实现

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "Parser.h"

namespace Zhaoyang{

	Parser::Parser(CharString str_):str(str_){
		
		//直接切取热点区域
		int prefix = str.indexOf(CharString("<div class=\"song_info_area\">"));
		int suffix = str.indexOf(CharString("<div class=\"music_list_area\">"));
		str = str.subString(prefix, suffix);


		Stack<Tag> stack;

		//开始解析文档
		for(int i=0; i<str.length(); ){
			while(i<str.length() && str[i]!='<'){
				i++;
			}
			if(i>=str.length()-2){
				break;
			}
			//found '<'

			if(str[i+1]=='/'){
				//found `</`
				Tag currentTag = stack.top();
				i = currentTag.end = str.indexOf('>',i)+1;
				allTags.push(currentTag);
				stack.pop();
			}else{
				//found a new tag name
				int endOfTagName = min_(str.indexOf(' ', i),str.indexOf('>', i));
				if(endOfTagName==CharString::NOT_FOUND)
					throw "closing '>' missing";
				else{
					endOfTagName -= 1;
				}
				CharString tagName = str.subString(i+1, endOfTagName+1);
				if(tagName.indexOf(CharString("img"))==0){
					//ignoring tags without the closing `</>`
					i = str.indexOf('>', i) + 1;
				}else{
					Tag tag(tagName);
					tag.start = i;
					i = tag.inner = str.indexOf('>', i) + 1;
					stack.push(tag);
				}
			}
		}
		if(!stack.empty())
			throw "found mismatch tag(s)";
		//整个文档解析完毕，全部节点已存入链表 `allTags`，
		//保存了每个标签的名称、始末位置，丢失嵌套层次关系
	}

	Parser::~Parser(){
		return;
	}

	SongInfo Parser::getSongInfo(){
		//遍历所有标签，根据标签名称提取信息
		//（链表的 operator[] 做了处理，用下标遍历仅耗线性时间）
		int length = allTags.length;
		int li=0;
		for(int ↑_↑=0; ↑_↑<length; ↑_↑++){
			Tag currentTag = allTags[↑_↑];
			if(currentTag.tagName.indexOf(CharString("h2"))==0){
				songInfo.title = (innerText(str.subString(currentTag.start, currentTag.end))).trim();
			}
			if(currentTag.tagName.indexOf(CharString("textarea"))==0){
				songInfo.lyric = (innerText(str.subString(currentTag.start, currentTag.end))).trim();
			}
			if(currentTag.tagName.indexOf(CharString("li"))==0){
				li++;
				CharString str_ = (innerText(str.subString(currentTag.start, currentTag.end))).trim();
				switch(li){
				case 1:
					songInfo.singer = str_.subString(6);/*magic number: length of "歌手："*/
					break;
				case 3:
					songInfo.album = str_.subString(10);
					break;
				case 4:
					songInfo.pubDate = str_.subString(10);
					break;
				default:
					break;
				}
			}
		}


		//下面从歌词的前两行提取词曲作者
		//谨以变量名表示抗议

		CharString ←_← = "曲：";
		CharString →_→ = "词：";
		int ↑_↑, ↑_↓=0, ↓_↑, ↓_↓=0;
		for(int ←_→=0; ←_→<=1; ←_→++){
			↑_↑ = songInfo.lyric.indexOf(←_←);
			if(↑_↑!=CharString::NOT_FOUND){
				↑_↓ = songInfo.lyric.indexOf('\n', ↑_↑);
				songInfo.composer = songInfo.lyric.subString(↑_↑+←_←.length(), ↑_↓);
				break;
			}
			if(!←_→)//应对 0009.html 的半角冒号
				←_← = CharString("曲:");
		}
		for(int ←_→=0; ←_→<=1; ←_→++){
			↓_↑ = songInfo.lyric.indexOf(→_→);
			if(↓_↑!=CharString::NOT_FOUND){
				↓_↓ = songInfo.lyric.indexOf('\n', ↓_↑);
				songInfo.lyricist = songInfo.lyric.subString(↓_↑+→_→.length(), ↓_↓);
				break;
			}
			if(!←_→) →_→ = CharString("词:");
		}
		int →_← = max_(↑_↓, ↓_↓);
		
		//应对样例 0003.html “两个曲作者”
		CharString ←_←_← = "编曲：";
		if(songInfo.lyric.indexOf(←_←_←, →_←)!=CharString::NOT_FOUND){
			int ←_→ = →_←+1;
			→_← = songInfo.lyric.indexOf('\n', →_←+1);
			songInfo.composer.append(',');
			CharString composerB = songInfo.lyric.subString(←_→+←_←_←.length(), →_←);
			songInfo.composer = songInfo.composer + composerB;
		}

		songInfo.lyric = (songInfo.lyric.subString(→_←)).trim();
		return songInfo;
	}

	int min_(int a, int b){
		if(a == CharString::NOT_FOUND)
			return b;
		if(b == CharString::NOT_FOUND)
			return a;
		return (a<b?a:b);
	}
	int max_(int a, int b){
		return (a>b?a:b);
	}
	CharString innerText(CharString str){
		CharString ret = str;
		// &lt; '<'
		int lt, rt;
		while(1){
			lt = ret.indexOf('<');
			if(lt == CharString::NOT_FOUND)
				break;
			rt = ret.indexOf('>', lt);
			ret = ret.subString(0, lt) + ret.subString(rt+1, -1);
		}
		return ret;
	}

}