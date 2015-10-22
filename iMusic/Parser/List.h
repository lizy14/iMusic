/*
�ļ���: List.h
�衡��: ���������ݽṹ ˫��ѭ������ ģ���� ������ʵ��

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once
#include <ostream>

namespace Zhaoyang{
	template<class T>
	class Item{
	public:
		T data;
		Item<T> *prev;
		Item<T> *next;
		Item():next(nullptr),prev(nullptr){}
	};

	template<class T>
	class List{
	public:
		Item<T> *head;
		Item<T> *tail;
		int length;
	public:
		List():
			head(nullptr),tail(nullptr),length(0),
			lastQueryPointer(nullptr){}
		~List(){
			Item<T> *p = head, *q;
			while(p!=nullptr){
				q = p;
				p = p->next;
				//TODO: ����ָ��/д�������캯��
				//delete q;
			}
		}
		void push(T item){
			length++;
			Item<T> *p = new Item<T>();
			p->data = item;
			if(tail==nullptr){
				tail = head = p;
			}else{
				tail->next = p;
				p->prev = tail;
				tail = p;
			}
		}
		bool empty(){
			return (head==nullptr);
		}
		int lastQueryIndex;
		Item<T> *lastQueryPointer;
		T operator[](int index){
			//TODO: ������һ���±��ѯ�Ľ��
			//����һ����ʹ���±��������ֻ������ʱ��
			int i;
			Item<T> *p;
			if(lastQueryPointer!=nullptr){
				i=lastQueryIndex;
				p=lastQueryPointer;
			}else{
				i=0;
				p=head;
			}
			do{
				if(i == index){
					lastQueryIndex = i;
					lastQueryPointer = p;
					return p->data;
				}
				if(i<index){
					i++;
					p=p->next;
				}else{
					i--;
					p=p->prev;
				}

			}while(p != nullptr);
			throw "Index out of range";
		}
	};

}


