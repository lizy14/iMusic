/*
�ļ���: Stack.h
�衡��: ��ջ�����ݽṹ ģ���� ������ʵ��

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
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

