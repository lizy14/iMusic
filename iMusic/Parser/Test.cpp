/*
文件名: Tests.cpp
描　述: 测试

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-17

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/
#include "Test.h"
namespace N{
	void test(){
		kmp();
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
		String sentence="the quick brown fox";
		String word="brown";
		cout << sentence.indexOf('w') << endl; //13
		cout << sentence.indexOf(word) << endl; //10

		int a = sentence.indexOf(String("quick"));
		int b = sentence.indexOf(String("fox"));
		cout << sentence.subString(a, b) << endl;//`quick brown `
		cout << String("hello, ")+String("world") << endl;
	}

}
