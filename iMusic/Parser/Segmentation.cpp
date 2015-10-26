/*
文件名: Segmentation.cpp
描　述: 中文分词器类的实现

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "Segmentation.h"
namespace Zhaoyang{
	const int Segmentation::MAX_WORD_LENGTH = 10;
	const int Segmentation::MIN_WORD_LENGTH = 2;

	bool Segmentation::isWord(CharString word){
		auto i = vocabulary.find(word);
		if(i != vocabulary.end()){
			return true;
		}
		return false;
	}
	
	//constructor: load library here
	Segmentation::Segmentation(CharString configFileName){
		
		std::ifstream file(configFileName);
		std::string vocabularyFileName;
		getline(file, vocabularyFileName);
		file.close();
		file.open(vocabularyFileName);
		std::string _;
		while(!file.eof()){
			getline(file, _);
			vocabulary.insert(_);
		}
	}

	Segmentation::~Segmentation(void){
	}

	CharStringList Segmentation::exec(CharString str){
		CharStringList list = CharStringList();
		if(str.length() == 0)
			return list;
		int iA = 0; //starting index 
		int iB = 0; //length of currently checking word 
		int inEnglishWord = false;
		int iC = 0; //start of an english word
		CharString word;
		while(iA < str.length()){

			if(CharString::isASCII(str[iA])){
				//meet an ascii charactor
				if(CharString::isSpace(str[iA])){
					iA ++;
					continue;
				}
				if( (iA+1)<str.length()
					&& (!CharString::isASCII(str[iA+1])
					|| CharString::isSpace(str[iA+1]))){
						//the next one is a non-ascii or space

						if(inEnglishWord){
							list.push(str.subString(iC, iC + iB + 1));
							iA = iC + iB + 1;
						}else{
							list.push(str.subString(iA, iA + 1));
							iA += 1;
						}
						inEnglishWord = false;
						continue;
						
				}else{
					if(iA+1==str.length()){
						list.push(str.subString(iA, iA+1));
						break;
					}

					if(inEnglishWord){
						iB += 1;
					}else{
						iC = iA;
						iB = 1;
						inEnglishWord = true;
					}
					iA ++;
					continue;
				}
				continue;
			}

			iB = MAX_WORD_LENGTH;
			word = str.subString(iA, iA+iB);
			if(isWord(word)){
				list.push(word);
				iA += iB;
				continue;
			}else{
				while(iB > MIN_WORD_LENGTH){
					iB --;
					word = str.subString(iA, iA+iB);
					if(isWord(word)){
						list.push(word);
						iA += iB;
						goto outside_continue;
					}
				}
				//single-character word
				list.push(str.subString(iA, iA + iB));
				iA += iB;
				continue;
			}
outside_continue:
			continue;
		}
		return list;
	}
}
