/*
文件名: Stack.h
描　述: “栈”数据结构 模板类 声明和实现

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once
#include "List.h"
namespace N{
	template<class T>
	class Stack : public List<T>{
	public:
		Stack(){}
		~Stack(){}
		void pop(){
			if(tail == nullptr){
				throw "Stack is empty";
			}
			if(tail->prev){
				Item<T> *newTail = tail->prev;
				delete tail;
				newTail->next = nullptr;
				tail = newTail;
				return;
			}else{
				delete tail;
				head = tail = nullptr;
				return;
			}
		}
		T top(){
			if(tail == nullptr){
				throw "Stack is empty";
			}else{
				return tail->data;
			}
		}
	};
}

