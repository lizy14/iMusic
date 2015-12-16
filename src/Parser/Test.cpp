/*
�ļ���: Tests.cpp
�衡��: ����

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-17

������: Visual Studio 2012 (MSVC++ 11.0)
*/
#include "IO.h"
#include "Test.h"

namespace Zhaoyang{ namespace Test{
	void test(){
		//str();return;
		//seg();return;
		int argc_=4;
		char inputDirectory[]="O:\\iMusic\\bin\\pages";
		char outputDirectory[]="O:\\iMusic\\bin\\output\\";
		char *argv_[4];
		argv_[1] = "O:\\iMusic\\bin\\iMusic.config";
		argv_[2] = inputDirectory;
		argv_[3] = outputDirectory;
		entryPoint(argc_, argv_);
	}
	void parser(){
		Parser parser(std::string(""));
	}
	void seg(){
		Segmentation seg(CharString("E:\\ongoing\\iMusic\\bin\\test.config"));
		CharStringList list = seg.exec(CharString("��������ѧapple tree�γ���banana����ѧ��"));
		for(int i=0; i<list.length; i++)
			cout << list[i] << endl;
	}
	void printBool(bool b){
		cout << (b?"true":"false") <<endl;
	}
	void str(){
		CharString word1 = "�Ǽ�", word2 = "�Ǽ�";
		printBool(word1 < word2);
		printBool(word2 < word1);
		printBool(word1 < word1);
		return;

		CharString word = "world.";
        word[-1]='~';
		CharString sentence = "hello, ";
		CharString newSentence = sentence + word;
		
		sentence = newSentence;
		newSentence = newSentence + word;
		cout << newSentence;
	}
	void stack(){
		Stack<int> stack;
		stack.push(10);
		stack.push(11);
		stack.push(12);
		stack.push(13);
		while(!stack.empty()){
			cout << stack.top() << endl;
			stack.pop();
		}
	}
	void kmp(){
		CharString sentence="the quick brown fox";
		CharString word="brown";
		cout << sentence.indexOf('w') << endl; //13
		cout << sentence.indexOf(word) << endl; //10

		int a = sentence.indexOf(CharString("quick"));
		int b = sentence.indexOf(CharString("fox"));
		cout << sentence.subString(a, b) << endl;//`quick brown `
	}
}}
