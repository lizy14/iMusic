
/*
�ļ���: 
�衡��: ����

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-12-14

������: Visual Studio 2012 (MSVC++ 11.0)
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