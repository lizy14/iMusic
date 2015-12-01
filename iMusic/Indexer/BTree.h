/*
�ļ���: BTree.h
�衡��: B-��, ���廪��ѧ���ѧԺ�������ڡ����ݽṹ������ʵ��

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-12-01

������: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once

#include <vector>
#include <map>
namespace Zhaoyang{
    template<class KeyType, class ValueType>
    class BTree{
       
        std::map<KeyType, ValueType> map;

    public:
        
        ValueType& operator[](KeyType key){
            return map[key];
        }

    };
}
