/*
�ļ���: main.cpp
�衡��: ������ڵ㣺ʵ�� 1������ҳ��Ϣ����ȡ��ִ�

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "List.h"
#include "Parser.h"
#include "SongInfo.h"
#include "Stack.h"
#include "String.h"
#include "StringList.h"
#include <iostream>
using N::List;
using N::Parser;
using N::Song;
using N::Stack;
using N::String;
using N::StringList;
using std::cin;
using std::cout;
using std::endl;

#ifdef _DEBUG
void printArguments(int argc, char** argv){
	cout << argc << endl;
	for(int i=0; i<argc; i++){
		cout << argv[i] << endl;
	}
}
#endif
int help(){
	cout << "Usage: iMusic arg1 arg2 arg3" << endl << endl;
	cout << "    arg1: config file, `iMusic.config` by default." << endl;
	cout << "    arg2: input directory." << endl;
	cout << "    arg3: output directory." << endl << endl;
	return 0;
}
int entryPoint(int argc, char** argv){
	if(argc != 4){
		return help();
	}
#ifdef _DEBUG
	printArguments(argc, argv);
#endif

	return 0;
}

int main(int argc, char** argv){
	entryPoint(argc, argv);
	system("pause");
	return 0;
}