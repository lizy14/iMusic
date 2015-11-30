#pragma once


#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

#include "../Parser/CharString.h"
#include "../Parser/List.h"
#include "../Parser/SongInfo.h"
#include "../Parser/Segmentation.h"
namespace Zhaoyang{
    class Document{
    public:
        SongInfo *p;
        int count;
    public:
        Document():p(nullptr), count(0){}
        Document(SongInfo* p_, int c_=0):p(p_), count(c_){}
        operator SongInfo*(){
            return p;
        }
        int getCount(){
            return count;
        }

    };

    bool operator<(Document x, Document y);


    class InvertedIndex
    {
        List<SongInfo> list;
        std::map<CharString, std::set<Document> > map;
        Segmentation *seg;
    public:
        InvertedIndex(void);
        ~InvertedIndex(void);
        void add(SongInfo& song);
        std::vector<SongInfo*> query(CharString str);
    };
}
