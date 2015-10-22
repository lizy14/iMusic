/*
�ļ���: Parser.cpp
�衡��: HTML ���������ʵ��

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
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
	CharString removeTags(CharString str){
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

		//ֱ����ȡ�ȵ�����
		int prefix = str.indexOf(CharString("<div class=\"song_info_area\">"));
		int suffix = str.indexOf(CharString("<div class=\"music_list_area\">"));
		str = str.subString(prefix, suffix);


		Stack<Tag> stack;
		List<Tag> allTags;
		

		//��ʼ�����ĵ�
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
				Tag tag(str.subString(i+1, endOfTagName+1));
				tag.start = i;
				i = tag.inner = str.indexOf('>', i) + 1;
				stack.push(tag);
			}
		}
		//�����ĵ�������ϣ�ȫ���ڵ��Ѵ������� `allTags`��
		//������ÿ����ǩ�Ŀ�ʼ�����ݡ�����λ�ã���ʧǶ�ײ�ι�ϵ


		//�������������Ѱ����Ҫ����Ϣ
		//����� operator[] ���˴������±������������ʱ��
		int length = allTags.length;
		for(int i=0; i<length; i++){
			Tag currentTag = allTags[i];
			if(currentTag.tagName.indexOf(CharString("h2"))==0){
				songInfo.title = trim(removeTags(str.subString(currentTag.start, currentTag.end)));
			}
			if(currentTag.tagName.indexOf(CharString("textarea"))==0){
				songInfo.lyric = trim(removeTags(str.subString(currentTag.start, currentTag.end)));
			}
			if(currentTag.tagName.indexOf(CharString("li"))==0){
				songInfo.pubDate = trim(removeTags(str.subString(currentTag.start, currentTag.end)));
			}
		}
		
		return;
	}

	Parser::~Parser(){
		return;
	}
}