/*
文件名: String.cpp
描　述: 字符串类的实现

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "String.h"
namespace N{
	String::String(){
		return;
	}

	String::~String(){
		return;
	}
	

	String String::subString(int start, int end){
		if(end==-1 || end>length())
			end = length();
		if(start<0)
			start = 0;
		String str;
		for(int i=start; i<end; i++){
			str.push_back(operator[](i));
		}
		return str;
	}

	//find W(word) in S(sentence)
	//return the index of the first appearance
	//implementing KMP algorithm
	int String::indexOf(String W){
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

	int String::indexOf(char chr){
		int i=0;
		for(char chr_: *this){
			if(chr_ == chr)
				return i;
			i++;
		}
		return NOT_FOUND;
	}

	std::ostream& operator<< (std::ostream& os, const String& str){
		for(char chr : str)
			os << chr;
		return os;
	}

	String operator+(const String& str1, const String& str2){
		String str;
		for(char chr : str1)
			str.push_back(chr);
		for(char chr : str2)
			str.push_back(chr);
		return str;
	}
}
