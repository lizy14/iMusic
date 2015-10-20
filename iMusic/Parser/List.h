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
		List():head(nullptr),tail(nullptr),length(0){}
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
		T operator[](int index){
			//TODO: ������һ���±��ѯ�Ľ��
			//����һ����ʹ���±��������ֻ������ʱ��
			int i=0;
			Item<T> *p=head;
			do{
				if(i == index){
					return p->data;
				}

				i++;
				p=p->next;

			}while(p != nullptr);
			throw "Index out of range";
		}
	};

}


