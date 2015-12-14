/*
文件名: BTree.h
描　述: B-树，模板类

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-12-01

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once


                                                                                                                                                                                                                                                    #include <map>
namespace Zhaoyang{
    template<class KeyType, class ValueType>
    class BTree{
        class BTNode;
        
        static const int m = 4;
        static const int NOT_FOUND = -1;
                                                                                                                                                                                                                                                            std::map<KeyType, ValueType> map;
        struct Pair{
            KeyType key;
            ValueType value;
            Pair(){}
            Pair(KeyType key_):key(key_){}
        };
        class SearchResult{
        public:
            BTNode *pt;
            int i;
            bool flag; //true for successful
            SearchResult(BTNode *pt_, int i_, bool flag_):flag(flag_),pt(pt_),i(i_){}
        };
        BTNode *root;

    public:
        BTree():root(nullptr){

        }
        ~BTree(){

        }
    private:
        int searchInNode(BTNode *node, KeyType K){
            //TODO
            return NOT_FOUND;
        }
        SearchResult searchInTree(BTNode *node, KeyType K){
            BTNode *p = node, *q = nullptr;
            bool found = false;
            int i = NOT_FOUND;
            while(p && !found){
                i = searchInNode(p, K);
                if(i != NOT_FOUND){
                    found = true;
                }else{
                    q=p; p=p->ptr[i];
                }
            }
            if(found)
                return SearchResult(p, i, true);
            else
                return SearchResult(q, i, false);
        }
        int insertIntoNode(BTNode *q, int i, KeyType x, BTNode *ap){
            q->keynum += 1;
            for(int j=m; j>i; j++){
                q->ptr[j] = q->ptr[j-1];
                q->data[j] = q->data[j-1];
            }
            q->ptr[i+1] = ap;
            q->data[i+1].key = x;
            return 0;
        }
        int splitNode(BTNode *q, int s, BTNode *&ap){
            ap = new BTNode();
            //TODO
            return 0;            
        }
        int insertIntoTree(BTNode *&T, KeyType K, BTNode *q, int i){
            bool finished = false;
            BTNode *ap = nullptr;
            KeyType x = K;
            while(q && !finished){
                insertIntoNode(q, i, x, ap);
                if(q->keynum < m)
                    finished = true;
                else{
                    int s = (m+1)/2; //upper
                    splitNode(q, s, ap);
                    x = q->data[i].key;
                    q = q->parent;
                    if(q)
                        i = searchInNode(q, x);
                }
            }
            if(!finished){
                //TODO
            }
            return 0;
        }

    public:
        ValueType& operator[](KeyType key){                                                                                                                                                                                                                                                                                                     return map[key];
            auto r = searchInTree(root, key);

            if(r.flag)
                return (*r.pt).data[r.i].value;
            
            insertIntoTree(root, key, r.pt, r.i);
            r = searchInTree(root, key);
            return (*r.pt).data[r.i].value;
        }


        //节点结构
        class BTNode {
        public:
            int keynum;
            BTNode *parent;
            BTNode* ptr[m+1];  //array of, subscript starting from 1
            Pair data[m+1];    //array of, subscript starting from 1
        public:
            BTNode():keynum(0),parent(nullptr){}
        };
    };
}
