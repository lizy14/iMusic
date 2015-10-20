/*
文件名: CharString.cpp
描　述: 字符串类的实现

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "CharString.h"
namespace Zhaoyang{
	const int CharString::REALLOCATE_SIZE = 1024;

	CharString::CharString():head(nullptr),len(0),capacity(0){
		return;
	}
	CharString::CharString(std::string str):head(nullptr),len(0),capacity(0){
		for(char chr: str)
			append(chr);
		return;
	}
	CharString::~CharString(){
		//TODO: 智能指针/写拷贝构造函数
		//delete[] head;
		return;
	}
	char& CharString::operator[](int i) const{
		if(i<0)
			i += len;
		if(i<0 || i>=len)
			throw "Subscript out of range";
		return head[i];
	}
	void  CharString::append(char chr){
		if(len == capacity){
			char *p = new char[len+REALLOCATE_SIZE];
			for(int i=0; i<len; i++){
				p[i] = operator[](i);
			}
			delete[] head;
			head = p;
			capacity += REALLOCATE_SIZE;
		}
		head[len]=chr;
		len++;

	}
	int CharString::length()const{
		return this->len;
	};

	CharString CharString::subString(int start, int end){
		if(end==-1 || end>length())
			end = length();
		if(start<0)
			start = 0;
		CharString str;
		for(int i=start; i<end; i++){
			str.append(operator[](i));
		}
		return str;
	}

	//find W(word) in S(sentence)
	//return the index of the first appearance
	//implementing KMP algorithm
	int CharString::indexOf(CharString W) const{
		if(W.length() == 0)
			return NOT_FOUND;
		if(W.length() == 1)
			return indexOf(W[0]);

		//first, make the table
		std::vector<int> T(W.length());
		int pos=2, cnd=0;
		T[0] = -1;
		T[1] = 0;

		while(pos < W.length()){
			if(W[pos-1] == W[cnd]){
				cnd = cnd + 1;
				T[pos] = cnd;
				pos = pos + 1;
			}else if(cnd > 0){
				cnd = T[cnd];
			}else{
				T[pos] = 0;
				pos = pos + 1;
			}
		}


		//now let's do KMP 
		int m=0, i=0;
		while((m + i) < length()){
			if(W[i] == operator[](m+i)){
				if(i == W.length() - 1)
					return m;
				i = i + 1;
			}else{
				if(T[i] > -1){
					m = m + i - T[i];
					i = T[i];
				}else{
					i = 0;
					m = m + 1;
				}
			}
		}
		return NOT_FOUND;
	}

	int CharString::indexOf(char chr) const{
		int i=0;
		for(int i=0; i<length(); i++){
			if(chr == operator[](i))
				return i;
		}
		return NOT_FOUND;
	}

	std::ostream& operator<< (std::ostream& os, const CharString& str){
		for(int i=0; i<str.length(); i++){
			os << str[i];
		}
		return os;
	}

	CharString operator+(const CharString& str1, const CharString& str2){
		CharString str;
		for(int i=0; i<str1.length(); i++){
			str.append(str1[i]);
		}
		for(int i=0; i<str2.length(); i++){
			str.append(str2[i]);
		}
		return str;
	}
}
