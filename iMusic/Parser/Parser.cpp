/*
文件名: Parser.cpp
描　述: HTML 解析器类的实现

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "Parser.h"

namespace Zhaoyang{
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
	bool isSpace(char chr){
		char space[]={' ','\n', '\r', '\t'};
		int nSpace = sizeof(space)/sizeof(char);
		for(int i=0; i<nSpace; i++){
			if(space[i]==chr)
				return true;
		}
		return false;
	}
	CharString trim(CharString str){
		CharString ret;
		int left = 0, right = str.length()-1;
		if(right<=left)
			return str;
		while(1){
			if(isSpace(str[left]))
				left++;
			else
				break;
		}
		while(1){
			if(isSpace(str[right]))
				right--;
			else
				break;
		}
		ret = str.subString(left, right+1);
		return ret;
	}
	Parser::Parser(CharString str){

		//直接切取热点区域
		int prefix = str.indexOf(CharString("<div class=\"song_info_area\">"));
		int suffix = str.indexOf(CharString("<div class=\"music_list_area\">"));
		str = str.subString(prefix, suffix);


		Stack<Tag> stack;
		List<Tag> allTags;
		

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


		//下面遍历该链表，根据标签名称提取信息
		//（链表的 operator[] 做了处理，用下标遍历仅耗线性时间）
		int length = allTags.length;
		int li=0;
		for(int i=0; i<length; i++){
			Tag currentTag = allTags[i];
			if(currentTag.tagName.indexOf(CharString("h2"))==0){
				songInfo.title = trim(innerText(str.subString(currentTag.start, currentTag.end)));
			}
			if(currentTag.tagName.indexOf(CharString("textarea"))==0){
				songInfo.lyric = trim(innerText(str.subString(currentTag.start, currentTag.end)));
			}
			if(currentTag.tagName.indexOf(CharString("li"))==0){
				li++;
				CharString str_ = trim(innerText(str.subString(currentTag.start, currentTag.end)));
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
		CharString i__ = "曲：";
		CharString j__ = "词：";
		int i, i_=0, j, j_=0;
		i = songInfo.lyric.indexOf(i__);
		if(i!=CharString::NOT_FOUND){
			i_ = songInfo.lyric.indexOf('\n', i);
			songInfo.composer = songInfo.lyric.subString(i+i__.length(), i_);
		}
		j = songInfo.lyric.indexOf(j__);
		if(j!=CharString::NOT_FOUND){
			j_ = songInfo.lyric.indexOf('\n', j);
			songInfo.lyricist = songInfo.lyric.subString(j+j__.length(), j_);
		}

		int k = max_(i_, j_);
		songInfo.lyric = trim(songInfo.lyric.subString(k+1));
		return;
	}

	Parser::~Parser(){
		return;
	}
}