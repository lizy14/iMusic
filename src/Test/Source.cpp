
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
    for(int i=0; i<5; i++){
        tr[i] = i + .233;
    }

    tr.travel([](BTree<int, double>::Pair p){
        cout << p.key << " => " << p.value << endl;
    });

    return system("pause");
}