
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
   
    auto pugongying = CharString("�ѹ�Ӣ");
    t[pugongying] = 233;
    cout << t[pugongying] << endl;
    t[CharString("��")] = 88;
    cout << t[pugongying] << endl;
    t[CharString("Լ��")] = 88;
    cout << t[pugongying] << endl;
    t[CharString("Сѧ")] = 88; 
    cout << t[pugongying] << endl;
    t[CharString("���")] = 88;
    cout << t[pugongying] << endl;
    t[CharString("��")] = 88;
    cout << t[pugongying] << endl;
    t[CharString("��")] = 88;
    cout << t[pugongying] << endl;
    t[pugongying] = 88;
    cout << t[pugongying] << endl;
    t[CharString("��")] = 88;
    t[CharString("����")] = 88;
    t[CharString("��")] = 88;
    t[CharString("��")] = 88;
    t[CharString("ζ��")] = 88;

    return system("pause");
}