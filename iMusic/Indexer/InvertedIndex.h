/*
�ļ���: InvertedIndex.h
�衡��: �����ĵ�

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 

������: Visual Studio 2012 (MSVC++ 11.0)
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
        //�������и�����Ϣ�������е����� `SongInfo*` ָ���ָ�����С�
        List<SongInfo> songs;
        //�ؼ��ʴʵ�
        typedef BTree<CharString, KeyWordData > Keywords;
        Keywords keywords;
        //�ִ���ʵ��
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

    //�ʵ�Ľڵ�
    struct KeyWordData{
        List<SongWithStatistics> list;
        int numberOfSongs;
        int numberOfAppearances;
        KeyWordData():numberOfAppearances(0),numberOfSongs(0){}
    };




    //�ڸ����ϸ���ͳ����Ϣ��ÿ�������治ͬ�ؼ��ʶ���ͬ
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

    //������Ȩ��ÿ�������治ͬ��������ͬ��������������ʱʹ��
    struct WeightedSong{
        SongInfo *p;
        int weight;
        WeightedSong(SongInfo* p_=nullptr, int c_=0):p(p_), weight(c_){}
    };
}
