/*
文件名: main.cpp
描　述: 程序入口点：实验 1——网页信息的提取与分词

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "IO.h"
#include "Test.h"
int main(int argc, char** argv){
	//for debugging
	//Test::test(); return system("pause");

	//for assignment submission
	try{
		entryPoint(argc, argv);
		return system("pause") && 0;
	}catch(char* e){
		cout << "ERROR: " << e;
		return system("pause") || 1;
	}
}
