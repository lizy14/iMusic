/*
文件名: List.h
描　述: “链表”数据结构 双向不循环链表 模板类 声明和实现

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once
#include <ostream>

namespace N{
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
				delete q;
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
			//保存上一次下标查询的结果
			//这样一来，使用下标遍历链表只需线性时间
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


