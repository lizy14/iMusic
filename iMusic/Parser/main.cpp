/*
�ļ���: main.cpp
�衡��: ������ڵ㣺ʵ�� 1������ҳ��Ϣ����ȡ��ִ�

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
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
