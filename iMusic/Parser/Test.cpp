/*
�ļ���: Tests.cpp
�衡��: ����

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-17

������: Visual Studio 2012 (MSVC++ 11.0)
*/
#include "Test.h"
namespace Zhaoyang{ namespace Test{
	void test(){
		str();
	}
	void seg(){
		;
	}
	void str(){
		cout << CharString("hello, ")+CharString("world") << endl;
		CharString str ="goodbye, world.";
		str[-1]='~';
		cout << str;
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
