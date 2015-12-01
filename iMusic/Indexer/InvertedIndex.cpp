#include "InvertedIndex.h"

namespace Zhaoyang{
InvertedIndex::InvertedIndex(void)
{
    puts("Loading vocabulary...");
    seg = new Segmentation(CharString("iMusic.config"));
    puts("Done.");
}


InvertedIndex::~InvertedIndex(void)
{
    delete seg;
}

void InvertedIndex::insert(SongInfo& song){
    songs.push(song);


    SongInfo* pSong = &songs.tail->data;

    CharStringList wordsInTitle = seg->exec(song.title);
    for(int i=0; i<wordsInTitle.length; i++){
        Statistics s;
        keywords[wordsInTitle[i]].numberOfAppearances ++;
        auto& songsWithThisWord = keywords[wordsInTitle[i]].list;
        auto *existing = songsWithThisWord.find(pSong);
        if(existing){
            s = existing->s;   
            s.numberOfAppearencesInTitle +=1;
            songsWithThisWord.find(pSong)->s = s;
        }else{
            s.numberOfAppearencesInTitle +=1;// =1;
            songsWithThisWord.push(SongWithStatistics(pSong, s));
        }
        
    }

    CharStringList wordsInLyric = seg->exec(song.lyric);
    for(int i=0; i<wordsInLyric.length; i++){
        Statistics s;
        CharString& word = wordsInLyric[i];

        keywords[wordsInLyric[i]].numberOfAppearances ++;
        auto& songsWithThisWord = keywords[wordsInLyric[i]].list;
        auto *existing = songsWithThisWord.find(pSong);
        if(existing){
            s = existing->s;   
            s.numberOfAppearencesInLyric +=1;
            songsWithThisWord.find(pSong)->s = s;
        }else{
            s.numberOfAppearencesInLyric +=1;// =1;
            songsWithThisWord.push(SongWithStatistics(pSong, s));
        }
    }
}

std::vector<SongInfo*> InvertedIndex::query(CharStringList wordsInQuery){
    //检索结果集
    std::map<SongInfo*, bool> songs;

    //每一检索结果的权 := 对查询串中各词的权之和
    std::map<SongInfo*, int> songsWeight;


    
     

    for(int i=0; i<wordsInQuery.length; i++){
        auto& keywordInfo = keywords[wordsInQuery[i]];
        auto& listOfDocuments = keywordInfo.list;
        for(int i=0; i<listOfDocuments.length; i++){
            songs[listOfDocuments[i].p] = true;
            songsWeight[listOfDocuments[i].p] +=
                10 * (listOfDocuments[i].s.numberOfAppearencesInTitle)
                + (listOfDocuments[i].s.numberOfAppearencesInLyric);
        }
    }

    //下面根据权进行排序
    std::vector<WeightedSong> vSongs;
    for(auto& i: songs)
        vSongs.push_back(WeightedSong(i.first, songsWeight[i.first]));

    std::sort(vSongs.begin(), vSongs.end(), [](WeightedSong a, WeightedSong b){
        return a.weight > b.weight;
    });

    //剥除权信息，以返回结果
    std::vector<SongInfo*> vSongsRet;
    for(auto& i: vSongs){
        vSongsRet.push_back(i.p);
    }

    return vSongsRet;
}

void InvertedIndex::test(){
    
}

}


