/*
�ļ���: List.h
�衡��: ���������ݽṹ ģ���� ������ʵ��

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once

namespace N{
	template<class Type> class List{

	public:
		List();
		~List();
		void push(Type);
	};
}

template<class Type>
void N::List<Type>::push(Type){
	return;
}

template<class Type>

N::List<Type>::List(){
	return;
}

template<class Type>
N::List<Type>::~List(){
	return;
}

