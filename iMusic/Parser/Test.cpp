/*
文件名: Tests.cpp
描　述: 测试

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-17

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/
#include "IO.h"
#include "Test.h"

namespace Zhaoyang{ namespace Test{
	void test(){
		int argc_=4;
		char inputDirectory[]="O:\\iMusic\\pages";
		char outputDirectory[]="O:\\iMusic\\output\\";
		char *argv_[4];
		argv_[1] = "THERE_IS_NO_CONFIG_FILE";
		argv_[2] = inputDirectory;
		argv_[3] = outputDirectory;
		entryPoint(argc_, argv_);
	}
	void parser(){
		Parser parser(std::string(""));
	}
	void seg(){
		;
	}
	void str(){

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
