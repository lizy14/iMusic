/*
文件名: List.h
描　述: “链表”数据结构 模板类 声明和实现

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
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

