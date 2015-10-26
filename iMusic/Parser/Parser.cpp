/*
�ļ���: Parser.cpp
�衡��: HTML ���������ʵ��

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "Parser.h"

namespace Zhaoyang{

	Parser::Parser(CharString str_):str(str_){
		
		//ֱ����ȡ�ȵ�����
		int prefix = str.indexOf(CharString("<div class=\"song_info_area\">"));
		int suffix = str.indexOf(CharString("<div class=\"music_list_area\">"));
		str = str.subString(prefix, suffix);


		Stack<Tag> stack;

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
		//�����ĵ�������ϣ�ȫ���ڵ��Ѵ������� `allTags`��
		//������ÿ����ǩ�����ơ�ʼĩλ�ã���ʧǶ�ײ�ι�ϵ
	}

	Parser::~Parser(){
		return;
	}

	SongInfo Parser::getSongInfo(){
		//�������б�ǩ�����ݱ�ǩ������ȡ��Ϣ
		//������� operator[] ���˴������±������������ʱ�䣩
		int length = allTags.length;
		int li=0;
		for(int ��_��=0; ��_��<length; ��_��++){
			Tag currentTag = allTags[��_��];
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
					songInfo.singer = str_.subString(6);/*magic number: length of "���֣�"*/
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


		//����Ӹ�ʵ�ǰ������ȡ��������
		//���Ա�������ʾ����

		CharString ��_�� = "����";
		CharString ��_�� = "�ʣ�";
		int ��_��, ��_��=0, ��_��, ��_��=0;
		for(int ��_��=0; ��_��<=1; ��_��++){
			��_�� = songInfo.lyric.indexOf(��_��);
			if(��_��!=CharString::NOT_FOUND){
				��_�� = songInfo.lyric.indexOf('\n', ��_��);
				songInfo.composer = songInfo.lyric.subString(��_��+��_��.length(), ��_��);
				break;
			}
			if(!��_��)//Ӧ�� 0009.html �İ��ð��
				��_�� = CharString("��:");
		}
		for(int ��_��=0; ��_��<=1; ��_��++){
			��_�� = songInfo.lyric.indexOf(��_��);
			if(��_��!=CharString::NOT_FOUND){
				��_�� = songInfo.lyric.indexOf('\n', ��_��);
				songInfo.lyricist = songInfo.lyric.subString(��_��+��_��.length(), ��_��);
				break;
			}
			if(!��_��) ��_�� = CharString("��:");
		}
		int ��_�� = max_(��_��, ��_��);
		
		//Ӧ������ 0003.html �����������ߡ�
		CharString ��_��_�� = "������";
		if(songInfo.lyric.indexOf(��_��_��, ��_��)!=CharString::NOT_FOUND){
			int ��_�� = ��_��+1;
			��_�� = songInfo.lyric.indexOf('\n', ��_��+1);
			songInfo.composer.append(',');
			CharString composerB = songInfo.lyric.subString(��_��+��_��_��.length(), ��_��);
			songInfo.composer = songInfo.composer + composerB;
		}

		songInfo.lyric = (songInfo.lyric.subString(��_��)).trim();
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