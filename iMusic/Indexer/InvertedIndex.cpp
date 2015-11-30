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

void InvertedIndex::add(SongInfo& song){
    list.push(song);


    SongInfo* pSong = &list.tail->data;

    CharStringList wordsInTitle = seg->exec(song.title);
    for(int i=0; i<wordsInTitle.length; i++){
        Document doc(pSong);
        auto& listOfCurrentKeyword = map[wordsInTitle[i]];
        auto existing = listOfCurrentKeyword.find(doc);
        if(existing != listOfCurrentKeyword.end()){
            doc.count = (*existing).count + 1;
            listOfCurrentKeyword.erase(existing);
        }
        listOfCurrentKeyword.insert(doc);
    }

    CharStringList wordsInLyric = seg->exec(song.lyric);
    for(int i=0; i<wordsInLyric.length; i++){
        Document doc(pSong);
        auto& listOfCurrentKeyword = map[wordsInLyric[i]];
        auto existing = listOfCurrentKeyword.find(doc);
        if(existing != listOfCurrentKeyword.end()){
            doc.count = (*existing).count + 1;
            listOfCurrentKeyword.erase(existing);
        }
        listOfCurrentKeyword.insert(doc);
    }
}

std::vector<SongInfo*> InvertedIndex::query(CharString str){
    //���������
    std::set<SongInfo*> songs;

    //ÿһ���������Ȩ := �Բ�ѯ���и��ʵ�Ȩ֮��
    std::map<SongInfo*, int> songsWeight;
    std::vector<Document> vSongs;

    CharStringList wordsInQuery = seg->exec(str);

    for(int i=0; i<wordsInQuery.length; i++){
        for(auto& i : map[wordsInQuery[i]]){
            songs.insert(i.p);
            songsWeight[i.p] += i.count;
        }
    }
    
    for(auto& i: songs)
        vSongs.push_back(Document(i, songsWeight[i]));

    std::sort(vSongs.begin(), vSongs.end(), [](Document a, Document b){
        return a.count > b.count;
    });

    //ȥ�������ɵ�Ȩ��Ϣ���Է��ؽ��
    std::vector<SongInfo*> vSongsRet;
    for(auto& i: vSongs){
        vSongsRet.push_back(i.p);
    }

    return vSongsRet;
}

inline bool operator<(Document x, Document y){
    return x.p < y.p;
}


}


