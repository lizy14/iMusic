
/*
文件名: 
描　述: 测试

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-12-14

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#include <cstdlib>
#include <iostream>

#include "../Indexer/BTree.h"
#include "../Parser/CharString.h"

using namespace std;
using namespace Zhaoyang;
int main(){
    BTree<int, double> tr;
        for(int i=0; i<10; i++){
        tr[i] = i + .233;
    }
    for(auto& i : tr)
        cout << i.key << " => " << i.value << endl;

    auto begin = tr.begin();
    auto end = tr.end();
    auto it = begin;
    while(1){
        if(!(it != end))
            break;

        cout << (*it).key << " => " << (*it).value << endl;
        
        it++;
    }
    for(auto& i : tr)
        cout << i.key << " => " << i.value << endl;
    
    return 0;

    BTree<CharString, int> t;
   
    auto pugongying = CharString("蒲公英");
    t[pugongying] = 233;
    cout << t[pugongying] << endl;
    t[CharString("的")] = 88;
    cout << t[pugongying] << endl;
    t[CharString("约定")] = 88;
    cout << t[pugongying] << endl;
    t[CharString("小学")] = 88; 
    cout << t[pugongying] << endl;
    t[CharString("篱笆")] = 88;
    cout << t[pugongying] << endl;
    t[CharString("旁")] = 88;
    cout << t[pugongying] << endl;
    t[CharString("的")] = 88;
    cout << t[pugongying] << endl;
    t[pugongying] = 88;
    cout << t[pugongying] << endl;
    t[CharString("是")] = 88;
    t[CharString("记忆")] = 88;
    t[CharString("里")] = 88;
    t[CharString("有")] = 88;
    t[CharString("味道")] = 88;

    return system("pause");
}