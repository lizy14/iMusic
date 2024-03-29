/*
文件名: CharString.cpp
描　述: 字符串类的实现

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "CharString.h"

namespace Zhaoyang{

	CharString::CharString():head(nullptr),len(0),capacity(0){
		return;
	}
	CharString::CharString(std::string str):head(nullptr),len(0),capacity(0){
		for(char chr: str)
			append(chr);
		return;
	}

	CharString::CharString(const CharString& str):head(nullptr),len(0),capacity(0){
		int oldLength = str.length();
		for(int i=0; i<oldLength; i++){
			append(str[i]);
		}
	}
    CharString::CharString(CharString& str):head(nullptr),len(0),capacity(0){
        int oldLength = str.length();
        for(int i=0; i<oldLength; i++){
            append(str[i]);
        }
    }
	CharString::~CharString(){
		delete[] head;
		return;
	}

	inline char& CharString::operator[](int i) const{
		if(i<0)
			i += len;
#ifdef _DEBUG
		if(i<0 || i>=len)
			throw "Subscript out of range";
#endif
		return head[i];
	}
	void CharString::append(char chr){
		if(len == capacity){
			char *p = new char[(len+1)*2];
			for(int i=0; i<len; i++){
				p[i] = operator[](i);
			}
			delete[] head;
			head = p;
			capacity = (len+1)*2;
		}
		head[len]=chr;
		len++;
	}
	inline int CharString::length() const{
		return this->len;
	};

	CharString CharString::subString(int start, int end) const{
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
	int CharString::indexOf(CharString W, int start) const{
		if(W.length() == 0)
			return NOT_FOUND;
		if(W.length() == 1)
			return indexOf(W[0], start);

		//first, make the table
		int* T = new int[W.length()];
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
		int m=start, i=0;
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

	int CharString::indexOf(char chr, int start) const{
		for(int i=start; i<length(); i++){
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
	CharString& CharString::operator=(const CharString& str){
		delete[] head;
		head=nullptr, len=0, capacity=0;
		int oldLength = str.length();
		for(int i=0; i<oldLength; i++){
			append(str[i]);
		}
		return *this;
	}
	bool operator==(const CharString& str1, const CharString& str2){
		int len = str1.length();
		if(len!=str2.length())
			return false;
		for(int i=0; i<len; i++){
			if(str1[i] != str2[i])
				return false;
		}
		return true;
	}
	bool CharString::operator<(const CharString& str1) const{
		int len;
		if(str1.length() != length())
			return (str1.length() < length());//len = str1.length();
		else
			len = length();

		for(int i=0; i<len; i++){
			if(str1[i] == operator[](i))
				continue;
			return (str1[i] < operator[](i));
		}
		//identical
		return false;//str1IsShorter;
	}


	bool CharString::isSpace(char chr){
		char space[]={' ','\n', '\r', '\t'};
		int nSpace = sizeof(space)/sizeof(char);
		for(int i=0; i<nSpace; i++){
			if(space[i]==chr)
				return true;
		}
		return false;
	}
	 bool CharString::isASCII(char chr){
		return (chr<128 && chr>0);
	}
	CharString CharString::trim(){
		CharString ret;
		int left = 0, right = length()-1;
		if(right<=left)
			return *this;
		while(1){
			if(isSpace(operator[](left)))
				left++;
			else
				break;
		}
		while(1){
			if(isSpace(operator[](right)))
				right--;
			else
				break;
		}
		ret = subString(left, right+1);
		return ret;
	}
}
