/*
文件名: BTree.h
描　述: B-树，模板类，
　　　  保存 key-value 对，等效于 std::map<>，
　　　  对外提供 operator[] 和 STL 风格迭代器

　　　  参考书目：《算法导论》第三版

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-12-14

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once

#include <vector>
#include <stack>

namespace Zhaoyang{
    
    template<class KeyType, class ValueType>
    class BTree{
        static const int t = 2; //minimum degree, >= 2
        
        struct Pair{
            KeyType key;
            ValueType value;
            Pair(KeyType _, ValueType __):key(_), value(__){}
            Pair(){}
        };

        class Node{
            int n; //number of keys in this node, <= 2t-1
            std::vector<Pair> data; //size == n
            std::vector<Node*> children; //size == n+1
            bool isLeaf;

            void makeNonLeaf(bool __ = true){
                
                if(children.size() == 0){
                    data.resize(2*t-1);
                    children.resize(2*t);
                    if(__)
                        for(int i=0; i<children.size(); i++)
                            children[i] = new Node(true, false);
                }
            }
            Node(bool _, bool __ = true):isLeaf(_), n(0){
                data.resize(2*t-1);
                children.resize(2*t);
                if(__)
                    makeNonLeaf(false);
            }
            friend class BTree;
        };

        Node *root;

        struct SearchResult{
            bool success;
            Node* node;
            int index;
            SearchResult(bool _, Node* __, int ___):success(_), node(__), index(___){}
        };

    private:


        SearchResult search(Node* x, KeyType& k){
            int i=1;
            if(x->n == 0)
                return SearchResult(false, x, i);
            while(i <= x->n && k > x->data[i-1].key)
                i++;

            if(i <= x->n && k == x->data[i-1].key)
                return SearchResult(true, x, i-1);

            if(x->isLeaf)
                return SearchResult(false, x, i-1);

            return search(x->children[i-1], k);

        }

        /*
        `x`: an nonfull internal node
        `i`: the index of a full child node of x
        */
        void splitChild(Node* x, int i){
            auto y = x->children[i-1];
            if(!y->isLeaf)
                y->makeNonLeaf();
            auto z = new Node(y->isLeaf);

            z->n = t - 1;
            for(int j=1; j<=t-1; j++)
                z->data[j-1] = y->data[j+t-1];

            if(!y->isLeaf)
                for(int j=1; j<=t; j++)
                    z->children[j-1] = y->children[j+t-1];

            y->n = t - 1;
            for(int j=x->n + 1; j>=i + 1; j--)
                x->children[j+1 -1] = x->children[j -1];
            x->children[i] = z;
            
            for(int j=x->n; j>=i; j--)
                x->data[j+1 -1] = x->data[j-1];
            x->data[i-1] = y->data[t-1];
            x->n ++;
        }

        void insert_nonfull(Node* x, KeyType& k, ValueType& v){
            auto i = x->n;
            if(x->isLeaf){
                while(i>=1 && k < x->data[i-1].key){
                    x->data[i] = x->data[i-1];
                    i--;
                }
                x->data[i] = Pair(k, v);
                x->n ++;
            }else{
                while(i>=1 && k < x->data[i-1].key){
                    i--;
                }
                i++;
                if(x->children[i-1]->n == 2*t-1){
                    splitChild(x, i);
                    if(k > x->data[i-1].key)
                        i++;
                }
                insert_nonfull(x->children[i-1], k, v);

            }
        }

        void insert(KeyType& k, ValueType& v){
            auto r = root;
            if(r->n == 2*t-1){

                auto s = new Node(false);
                root = s;
                s->children[1-1] = r;
                splitChild(s, 1);
                insert_nonfull(s, k, v);
            }
            else
                insert_nonfull(r, k, v);
        }
    public:
        BTree(){
            root = new Node(true);
        }
        ~BTree(){
            //TODO
        }
        ValueType& operator[](KeyType key){

            auto find = search(root, key);
            if(find.success)
                return find.node->data[find.index].value;
            else{
                auto newVal = ValueType();
                insert(key, newVal);
                auto find = search(root, key);
                if(!find.success)
                    throw "BTree internal error";
                return find.node->data[find.index].value;
            }
        }

    public:
        class BTreeIterator{
            friend class BTree;
            BTree* tree;
            struct Cursor{
                Node* node;
                int index; // -1 means "i am new here, seeing children"
                Pair getPair(){
                    return node->data[index];
                }
            };
            std::stack<Cursor> cursors;
            bool done;
        public:
            void operator++(){
                cursors.top().index ++;
                bool traceback = false;
                //back trace
                while(1){
                    auto top = cursors.top();
                    if(top.index >= top.node->n){
                        traceback = true;
                        cursors.pop();
                        if(cursors.empty()){
                            done = true;
                            return;
                        }
                        cursors.top().index ++;
                    }else
                        break;
                }

                if(traceback){
                    //go deep again
                    cursors.top().index ++;
                    auto p = cursors.top().node->children[cursors.top().index];
                    do{
                        BTreeIterator::Cursor cursor;
                        cursor.node = p;
                        cursor.index = -1;
                        if(!cursor.node)
                            break;
                        cursors.push(cursor);
                        if(!p || p->isLeaf)
                            break;
                        p = p->children[0];
                        if(!p)
                            break;
                    }while(1);
                }
                    

                auto& top = cursors.top();
                if(top.index == -1){
                    top.index ++;
                    return;
                }
            }
            Pair operator*(){
                return Pair(cursors.top().getPair());
            }
            bool operator!=(BTreeIterator it){
                if(done && it.done)
                    return false;
                //TODO
                return true;
            }
        };
        BTreeIterator begin(){
            BTreeIterator it;
            it.tree = this;
            it.done = false;
            Node* p = root;

            //go as deep as possible, finding the smallest keyword
            do{
                BTreeIterator::Cursor cursor;
                cursor.node = p;
                cursor.index = -1;
                it.cursors.push(cursor);
                if(p->isLeaf){
                    it.cursors.top().index ++;
                    break;
                }
                p = p->children[0];
            }while(1);

            return it;
        }
        BTreeIterator end(){
            BTreeIterator it;
            it.tree = this;
            it.done = true;
            return it;
        }
    };

}
