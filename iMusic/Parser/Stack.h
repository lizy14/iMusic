/*
�ļ���: Stack.h
�衡��: ��ջ�����ݽṹ ģ���� ������ʵ��

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once

namespace N{
	template<class Type>
	class Stack{
	public:
		Stack();
		~Stack();
		int pop();
		Type top();
		int push(Type);
	};
}

