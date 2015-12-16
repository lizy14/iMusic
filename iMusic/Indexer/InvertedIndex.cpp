/*
文件名: InvertedIndex.cpp
描　述: 

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

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
std::vector<SongInfo*> InvertedIndex::recommend(CharString name){
    
    std::vector<SongInfo*> ret;
    int minLength = -1, minID = -1;

    //find the song with shortest name, containing query string
    for(int i=0; i<songs.length; i++){
        if(songs[i].title.indexOf(name)!=CharString::NOT_FOUND){
            int length = songs[i].title.length();
            if(minLength == -1 || length < minLength){
                minID = i, minLength = length;
            }
        }
    }
    if(minID == -1)
        return ret;


    cout << "Generating recommendations for `" << songs[minID].title << "`...\n";

    auto& song = songs[minID];
    ret.push_back(&song);

    auto words = seg->exec(
        song.title + song.title + song.title + song.lyric);//gives title more weight
    auto searchResult = search(words);
    for(int i=0; i<10; i++){
        ret.push_back(searchResult[i].p);
    }
}
std::vector<WeightedSong> InvertedIndex::search(CharStringList wordsInQuery){
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

    return vSongs;
}

void InvertedIndex::test(){
    
}

}


