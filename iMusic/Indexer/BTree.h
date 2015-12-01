/*
文件名: BTree.h
描　述: B-树, 据清华大学软件学院张力教授《数据结构》讲义实现

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-12-01

环　境: Visual Studio 2012 (MSVC++ 11.0)
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
