/*
文件名: InvertedIndex.h
描　述: 倒排文档

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once



#include <vector>
#include <algorithm>
#include <map>

#include "BTree.h"
#include "../Parser/CharString.h"
#include "../Parser/List.h"
#include "../Parser/SongInfo.h"
#include "../Parser/Segmentation.h"
namespace Zhaoyang{



    struct WeightedSong;
    struct Statistics;
    struct SongWithStatistics;
    struct KeyWordData;
    

    class InvertedIndex
    {
        //储存所有歌曲信息。本类中的所有 `SongInfo*` 指针均指向其中。
        List<SongInfo> songs;
        //关键词词典
        typedef BTree<CharString, KeyWordData > Keywords;
        Keywords keywords;
        //分词器实例
        Segmentation *seg;
    public:
        InvertedIndex(void);
        ~InvertedIndex(void);
        Segmentation* getSeg(){return seg;}
        void insert(SongInfo& song);
        std::vector<WeightedSong> search(CharStringList wordsInQuery);
        std::vector<SongInfo *> recommend(CharString songName); //return[0] is the matching song
        void test();

    };

    //词典的节点
    struct KeyWordData{
        List<SongWithStatistics> list;
        int numberOfSongs;
        int numberOfAppearances;
        KeyWordData():numberOfAppearances(0),numberOfSongs(0){}
    };




    //在歌曲上附加统计信息，每个歌曲随不同关键词而不同
    struct Statistics{
        int numberOfAppearencesInTitle;
        int numberOfAppearencesInLyric;
        Statistics():numberOfAppearencesInLyric(0),numberOfAppearencesInTitle(0){}
    };
    struct SongWithStatistics{
        SongInfo *p;
        Statistics s;
        operator SongInfo*(){return p;}
        SongWithStatistics(SongInfo* p_, Statistics s_):p(p_),s(s_){}
        SongWithStatistics(SongInfo* p_=nullptr):p(p_){}
    };

    //歌曲带权，每个歌曲随不同检索而不同，仅在搜索排序时使用
    struct WeightedSong{
        SongInfo *p;
        int weight;
        WeightedSong(SongInfo* p_=nullptr, int c_=0):p(p_), weight(c_){}
    };
}
